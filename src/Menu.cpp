
/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#include "Menu.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

Menu::Menu() {
	//initialize messages to user as strings in the player options string vector
	playerOptions_[0] = "Choose white player's type: ";
	playerOptions_[1] = "play against a human player";
	playerOptions_[2] = "play against an AI player";
}


Player* Menu::getPlayerByUserChoice(ViewGame& view) {
	//call view to show menu and return player's option
	//TODO - not actually a nice way to do this... maybe we should split into "show" and "get choice" - one action per method
	int choice = view.presentMenu(playerOptions_);

	//create and return a player type according to user's choice TODO - should return by reference or as pointer?
	switch(choice) {
		case 0:
			//TODO - should the player by allowed to choose the color of the
			return new HumanPlayer("O", Board::WHITE);

		case 1:
			return new ComputerPlayer("O", Board::WHITE);

		default:
			view.showMessage("Problem creating players");
			break;
	}
	return new HumanPlayer("O",  Board::WHITE);
}
