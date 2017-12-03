
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
	 * Show the menu and accepts user's choice (then saves it).
	 * Uses the view to show the menu, then accepts a player's decision and acts upon it.
	 *
	 * @param view to show menu options with
	 */
	void show(ViewGame& view);

	/**
	 * Returns a type of player to play in game (human vs. AI), by the player's choice.
	 * Player's choice is saved from last showing of menu.
	 *
	 * @return a type of Player
	 */
	Player* getPlayerByUserChoice();

	/**
	 * Returns a type of game manager to manage the game (local vs. remote), by the player's choice.
	 * Player's choice is saved from last showing of menu.
	 * Must accept all arguments to allow creating the proper Game Manager.
	 *
	 * @param b board of game
	 * @param p1 black player
	 * @param p2 white player
	 * @param ml logic to handle moves
	 * @return a type of Game Manager
	 */
	GameManager* getGameManagerByUserChoice(ViewGame* v, Board& b, Player* p1, Player* p2, MoveLogic* ml);

private:
	//choice of user in last showing of menu
	int choice_;

	//vector to hold messages of options at index of choice. Using a vector for easy access to length along with easy iteration.
	std::vector<std::string> playerOptions_;
};



#endif /* MENU_H_ */
