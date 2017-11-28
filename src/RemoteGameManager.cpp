/*
 * RemoteGameManager.cpp
 */

#include "../include/RemoteGameManager.h"

RemoteGameManager::RemoteGameManager(ViewGame* view, Board& b, Player* black,
		Player* white, MoveLogic* log): GameManager(view, b, black, white, log) {
	//create client
}

/**
 * Plays game, where currPlayer is always the local player, and oppPlayer if the opposite player
 */
//DECLARE GLOBAL VARIABLES for all play...() functions
//declare flag - in first turn game has not been played, current player has moves
bool noMoves = false;
//declare move here - so we can show move later
Location move(-1,-1);

void RemoteGameManager::playGame() {
	//TODO
	//ask client to connect with server
	//read message - if we got "2" - switch players and play remot
	int color; //TODO


	view_->showMessage("Current board:");
	view_->printBoard(board_.getBoard(), board_.size());

	/* General explanation - First, build a list containing all the
	 * empty cells on the board. then, checking what might be a possible
	 * move dor the player, and putting all the options into a vector.
	 * The user select a point, and the board update acoording to the
	 *  selected point.
	 */

	//TODO - ask if we got "2" and local (currPlayer) is the white
	//if so - play remote's turn
	if (color == 2) {
		playRemoteTurn();
	}

	//declare flag for keeping track of game over
	bool continueGame = true;

	//while game is not over - keep playing, local player then remote
	while (!board_.isBoardFull())
	{
		//play local player's turn
		continueGame = playLocalTurn();

		//if game is over after local turn - break loop
		if (!continueGame) {
			break;
		}

		//play remote turn
		continueGame = playRemoteTurn();

		//if game is over after remote turn - break loop
		if (!continueGame) {
			break;
		}
	}

	//call show winner
	showWinner();
}


bool RemoteGameManager::playLocalTurn() {
	//display current turn
	view_->messageForTurn(currPlayer_->getName());

	//initialize moves for black and white players
	logic_->updateMoveOptions(currPlayer_, board_);

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

		//TODO - send chosen move to server

		//update flag
		noMoves = false;
	}
	//if current player cannot play his turn
	else
	{
		//if the second player cannot play - show message and switch turns
		if (!noMoves) {
			view_->messageSwitchTurns();

			//TODO - send "NoMove" via server

			noMoves = true;
		}
		else
		{
			//if both players did not play - game is over, there are no more moves left in game
			view_->showMessage("No possible moves for both players.");

			//TODO - send "EndGame" via server
			//sending is only needed when game was over during local turn (if during remote - message will be accepted, not sent)

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

}
