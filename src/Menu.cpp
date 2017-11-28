#include "../include/Menu.h"
#include "../include/HumanPlayer.h"
#include "../include/ComputerPlayer.h"

using namespace std;

Menu::Menu() {
	//initialize messages to user as strings in the player options string vector
	playerOptions_.push_back("Choose white player's type:"); //index 0
	playerOptions_.push_back("play against a human player"); //index 1
	playerOptions_.push_back("play against an AI player"); //index 2
}


Player* Menu::getPlayerByUserChoice(ViewGame& view) {
	//call view to show menu and return player's option
	//TODO - not actually a nice way to do this... maybe we should split into "show" and "get choice" - one action per method
	int choice = view.presentMenu(playerOptions_);

	//create and return a player type according to user's choice TODO - should return by reference or as pointer?
	switch(choice) {
		case 1:
			return new HumanPlayer("O", Board::WHITE);

		case 2:
			return new ComputerPlayer("O", Board::WHITE);

		default:
			view.showMessage("Problem creating players");
			break;
	}
	return new HumanPlayer("O",  Board::WHITE);
}
