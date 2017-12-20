/*
 * RemoteGameManager.cpp
 */

#include "../include/RemoteGameManager.h"
#include <stdlib.h> //for exit(-1)
#include <vector>
#include <string>
using namespace std;

RemoteGameManager::RemoteGameManager(ViewGame* view, Board& b, Player* black,
		Player* white, MoveLogic* log): GameManager(view, b, black, white, log) {}

/**
 * Plays game, where currPlayer is always the local player, and oppPlayer if the opposite player
 */
//DECLARE GLOBAL VARIABLES for all play...() functions
//declare flag - in first turn game has not been played, current player has moves
bool noMoves = false;

void RemoteGameManager::playGame() {
	//setup game (connect to server, choose to start\join a game)
	setup();

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
	bool local = false; //to know whether server should be notified

	//while game is not over - keep playing, local player then remote
	while (!board_.isBoardFull() && continueGame)
	{
		//play local player's turn
		continueGame = playLocalTurn();

		//if game is over after local turn - mark and break loop
		if (!continueGame || board_.isBoardFull()) {
			local = true;
			break;
		}

		//play remote turn
		continueGame = playRemoteTurn();

		//if game is over after remote turn - loop will be broken at while condition
	}

	//if game ended at remote turn - server should be notified to release the clients
	if (!local) {
		//send "EndGame" via server - sending is only needed when game was over during remote turn
		//(if during local - message will be accepted by the server from the other player - for him we are the remote)
		client_.sendEndGame();
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
	//initialize moves for remote player
	logic_->updateMoveOptions(oppPlayer_, board_);

	//let local player know that we are waiting for remote to play
	view_->showMessage("Waiting for other player's move...\n");


	//get remote's move via server
	//if remote has no moves, it will return as (-1,-1), and if remote disconnected, we will get (-2,-2)
	Location move = client_.acceptMove();


	//if other player disconnected - notify and return false
	if (move == Location(-2, -2)) {
			view_->showMessage("Other player disconnected, game has ended.\n");
			//return false - game is over
			return false;
	} else if (move != Location(-1, -1)) {
		//else, if remote player can play his turn - move returned is not (-1,-1)

		//move is assumed to be allowed - by instructions
		//call logic to play move
		logic_->playMove(move, oppPlayer_, board_, currPlayer_);

		//update flag
		noMoves = false;
	} else {
		//else, remote player cannot play his turn

		//if the only the remote player did not play - show message
		if (!noMoves) {
			view_->messageSwitchTurns();

			//update flag
			noMoves = true;
		} else {
			//else, both players did not play - game is over, there are no more moves left in game
			view_->showMessage("No possible moves for both players.");

			//return false - game is over
			return false;
		}
	}


	//show board
	view_->showMessage("\nCurrent board:");
	view_->printBoard(board_.getBoard(), board_.size());
	//show message of last turn - if was played
	if (!noMoves) {
		view_->messagePlayerMove(move, oppPlayer_->getName());
	}

	//return true - game continues
	return true;
}


void RemoteGameManager::setup() {
	//ask client to connect with server
	try {
		client_.connectToServer();
	} catch (const char *msg) {
		std::cout << "Failed to connect to server. Reason: " << msg << std::endl;
		exit(-1);
	}

	//notifying of connection
	view_->showMessage("Connected to server");

	//present remote game options
	vector<string> ops;
	ops.push_back("Remote game options:"); //push title
	ops.push_back("start a new game"); //first option
	ops.push_back("join an existing game"); //second option

	//get player's choice
	int choice = view_->presentMenu(ops);

	//if player chose to START A NEW GAME
	if (choice == 1) {
		//get new game's name
		string name = view_->getStringInput();

		//start the game - while name is an existing game name in the server's game list
		while (client_.startGame(name) == -1) {
			view_->showMessage("A game with this name already exists. Please choose a different name: ");
			name = view_->getStringInput();
		}

		//show waiting message
		view_->showMessage("Waiting for other player to join...");

	} else {
		//otherwise, choice is 2 (by presentMenu's definitions)
		//player chose to JOIN AN EXISTING GAME
		vector<string> games = client_.listGames();

		//prepare game names to present to user - create MESSAGE: join the game 'NAME'
		for (int i=0; i < games.size(); i++) {
			games[i] = "join the game '" + games[i] + "'";
		}

		//add title at index 0
		games.insert(games.begin(), "Please choose a game to join:");

		//show options to player, and get choice
		choice = view_->presentMenu(games);

		//join existing game - index of chosen game is one less then choice (index 0 is now the title)
		client_.joinGame(choice-1);
	}
}
