/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#ifndef MENU_H_
#define MENU_H_

#include "ViewGame.h"
#include "Player.h"
#include "MoveLogic.h"
#include <vector>

/**
 * Holds the options for different settings of the game, and knows to return the game's parameters accordingly.
 */
class Menu {
	public:
		/**
		 * Returns a type of player to play in game, by the given choice's index
		 * @param index index of option in the shown menu
		 * @return a type of Player
		 */
		Player& getPlayerChoice(int index);

		/**
		 * Returns a type of move logic (move rules) to play by in game, by the given choice's index
		 * @param index index of option in the shown menu
		 * @return a type of MoveLogic
		 */
		MoveLogic& getLogicChoice(int index);

		/**
		 * Options of different types of players, where the index is the key to press for choice,
		 * and the string at that index is the message for that choice
		 * @return string vector with the options' messages
		 */
		std::vector<std::string>& playerOptions();

		/**
		 * Options of different types of logics, where the index is the key to press for choice,
		 * and the string at that index is the message for that choice
		 * @return string vector with the options' messages
		 */
		std::vector<std::string>& logicOptions();
};



#endif /* MENU_H_ */
