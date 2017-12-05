/*
 * RemoteGameManager.cpp
 */

#include "../include/RemoteGameManager.h"
#include <stdlib.h> //for exit(-1)

//TODO - an okay number to pass as IP?
RemoteGameManager::RemoteGameManager(ViewGame* view, Board& b, Player* black,
		Player* white, MoveLogic* log): GameManager(view, b, black, white, log), client_("127.0.0.1", 8000) {}

/**
 * Plays game, where currPlayer is always the local player, and oppPlayer if the opposite player
 */
//DECLARE GLOBAL VARIABLES for all play...() functions
//declare flag - in first turn game has not been played, current player has moves
bool noMoves = false;

void RemoteGameManager::playGame() {
	//ask client to connect with server
	try {
		client_.connectToServer();
	} catch (const char *msg) {
		cout << "Failed to connect to server. Reason: " << msg << endl;
		exit(-1);
	}

	view_->showMessage("Connected to server");
	view_->showMessage("Waiting for other player to join...");

	//read message of the local player's color - waits for connection
	int color = client_.acceptColor();

	// let player know what color he is
	// if we got "2" - switch players to make current player the local one (the white)
	if (color == 2) {
		//show messsage
		view_->showMessage("You are the white (O) player");
		//switch players
		Player* temp = currPlayer_;
		currPlayer_ = oppPlayer_;
		oppPlayer_ = temp;
	} else {
		//otherwise - just show message
		view_->showMessage("You are the black (X) player");
	}

	view_->showMessage("Current board:");
	view_->printBoard(board_.getBoard(), board_.size());

	//if so - play remote's turn
	if (color == 2) {
		playRemoteTurn();
	}

	//declare flag for keeping track of game over
	bool continueGame = true;

	//while game is not over - keep playing, local player then remote
	//TODO - make sure logic works OK - ask Yaeli
	while (!board_.isBoardFull() && continueGame)
	{
		//play local player's turn
		continueGame = playLocalTurn();

		//if game is over after local turn - break loop
		if (!continueGame || board_.isBoardFull()) {
			break;
		}

		//play remote turn
		continueGame = playRemoteTurn();

		//if game is over after remote turn - loop will be broken at while condition
	}

	//call show winner
	showWinner();
}


bool RemoteGameManager::playLocalTurn() {
	//display current turn
	view_->messageForTurn(currPlayer_->getName());

	//initialize moves for local players
	logic_->updateMoveOptions(currPlayer_, board_);

	//declare move here - so we can show move later
	Location move(-1,-1);

	//if current player can play his turn
	if (logic_->canPlayTurn(currPlayer_)) {
		//show possible moves
		view_->messagePossibleMoves(currPlayer_->getPossibleMoves());

		//get next player's move
		move = currPlayer_->getNextMove(view_, logic_, board_,oppPlayer_);

		//check that move is allowed
		//while move isn't legal - get another move from player
		while (!logic_->isMoveAllowed(move, currPlayer_))
		{
			view_->showMessage("Illegal move, try again.");
			move = currPlayer_->getNextMove(view_, logic_, board_,oppPlayer_);
		}

		//call logic to play move
		logic_->playMove(move, currPlayer_, board_, oppPlayer_);

		//send chosen move to server
		client_.sendMove(move);

		//update flag
		noMoves = false;
	}
	//if current player cannot play his turn
	else
	{
		//if the second player cannot play - show message and send via server
		if (!noMoves) {
			view_->messageSwitchTurns();

			//send "NoMove" via server
			client_.sendNoMoves();

			noMoves = true;
		}
		else
		{
			//if both players did not play - game is over, there are no more moves left in game
			view_->showMessage("No possible moves for both players.");

			//send "EndGame" via server
			//sending is only needed when game was over during local turn (if during remote - message will be accepted by server, not sent)
			client_.sendEndGame();

			//return false - game is over
			return false;
		}
	}

	//show board and last moves
	view_->showMessage("\nCurrent board:");
	view_->printBoard(board_.getBoard(), board_.size());
	//message of last turn - if was played
	if (!noMoves) {
		view_->messagePlayerMove(move, currPlayer_->getName());
	}

	//return true - game continues
	return true;
}


bool RemoteGameManager::playRemoteTurn() {
	//display current turn
	view_->messageForTurn(oppPlayer_->getName());

	//initialize moves for remote player
	logic_->updateMoveOptions(oppPlayer_, board_);

	//get remote's move via server
	//if remote has no moves, it will return as (-1,-1)
	Location move = client_.acceptMove();

	//if remote player can play his turn - move returned is not (-1,-1)
	if (move != Location(-1, -1)) {
		//show possible moves
		view_->messagePossibleMoves(oppPlayer_->getPossibleMoves());

		//move is assumed to be allowed - by instructions TODO -true?
		//call logic to play move
		logic_->playMove(move, oppPlayer_, board_, currPlayer_);

		//update flag
		noMoves = false;
	}
	//if remote player cannot play his turn
	else
	{
		//if the remote player only player did not play - show message
		if (!noMoves) {
			view_->messageSwitchTurns();

			//update flag
			noMoves = true;
		}
		else
		{
			//if both players did not play - game is over, there are no more moves left in game
			view_->showMessage("No possible moves for both players.");

			//no need to send "EndGame" via server - sending is only needed when game was over during local turn
			//return false - game is over
			return false;
		}
	}

	//show board and last moves
	view_->showMessage("\nCurrent board:");
	view_->printBoard(board_.getBoard(), board_.size());
	//message of last turn - if was played
	if (!noMoves) {
		view_->messagePlayerMove(move, currPlayer_->getName());
	}

	//return true - game continues
	return true;
}
