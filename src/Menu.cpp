#include "../include/Menu.h"
#include "../include/HumanPlayer.h"
#include "../include/ComputerPlayer.h"
#include "../include/LocalGameManager.h"
#include "../include/RemoteGameManager.h"

using namespace std;

Menu::Menu() {
	//initialize messages to user as strings in the player options string vector
	playerOptions_.push_back("Choose white player's type:"); //index 0
	playerOptions_.push_back("play against a human player"); //index 1
	playerOptions_.push_back("play against an AI player"); //index 2
	playerOptions_.push_back("play against a remote player"); //index 3

	//intialize choice to -1, to stop from getting a choice before presenting menu
}

void Menu::show(ViewGame& view) {
	//call view to show menu and return player's option
	choice_ = view.presentMenu(playerOptions_);
}

Player* Menu::getPlayerByUserChoice() {
	//create and return a player type according to user's choice
	switch(choice_) {
	//in both cases 1,3 we use a human player as the opponent. When playing vs. a remote player the human
	//player acts as a "empty" player for playing the moves received from the ooponent via the server
	case 1:
	case 3:
		return new HumanPlayer("O", Board::WHITE);

	case 2:
		return new ComputerPlayer("O", Board::WHITE);

	default:
		throw("Problem creating players");
	}
}

GameManager* Menu::getGameManagerByUserChoice(ViewGame* v, Board& b, Player* p1, Player* p2, MoveLogic* ml) {
	//create and return a player type according to user's choice
	switch(choice_) {
	//in both cases 1,2 we use a local game manager
	case 1:
	case 2:
		return new LocalGameManager(v, b, p1, p2, ml);

	case 3:
		return new RemoteGameManager(v, b, p1, p2, ml);

	default:
		throw("Problem creating game manager");
	}
}
