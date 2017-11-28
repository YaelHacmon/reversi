
#ifndef MENU_H_
#define MENU_H_

#include "ViewGame.h"
#include "Player.h"
#include <vector>

/**
 * Holds the options for different settings of the game, and knows to return the game's parameters accordingly.
 * Allows use of the Factory design pattern for runtime creation of object types by the user's choice (Menu is the factory class).
 */
class Menu {
	public:
		/**
		 * Constructor, no parameters.
		 * Will initialize the options string array with messages for every index
		 */
		Menu();

		/**
		 * Returns a type of player to play in game, by the player's choice
		 * Uses the view to show the menu, then accepts a player's decision and acts upon it.
		 *
		 * @param view to show menu options with
		 * @return a type of Player
		 */
		Player* getPlayerByUserChoice(ViewGame& view);

	private:
		//vector to hold messages of options at index of choice. Using a vector for easy access to length along with easy iteration.
		std::vector<std::string> playerOptions_;
};



#endif /* MENU_H_ */
