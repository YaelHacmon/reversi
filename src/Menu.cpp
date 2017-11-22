/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#include "Menu.h"

using namespace std;

Menu::Menu() {
	//initialize messages to user as strings in the player options string vector
	playerOptions_[0] = "Choose white player's type: ";
	playerOptions_[1] = "play against a human player";
	playerOptions_[2] = "play against an AI player";
}


Player& Menu::getPlayerByUserChoice(ViewGame& view) {
	//call view to show menu and return player's option
	int choice = view.presentMenu(playerOptions_);

	//create and return a player type according to user's choice
	switch(choice) {
		case 0:
			return new HumanPlayer("O", Player::ColorOfPlayer::WHITE);

		case 1:
			return new ComputerPlayer("O", Player::ColorOfPlayer::WHITE);

		default:
			view.showMessage("Problem creating players");
			break;
	}

	//must return from method - this should never be executed
	return new HumanPlayer("O", Player::ColorOfPlayer::WHITE);
}
