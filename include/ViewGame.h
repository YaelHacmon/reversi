/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#ifndef VIEWGAME_H_
#define VIEWGAME_H_
#include "Board.h"
#include <vector>

using namespace std;

// this cladd represent the view of the game. all the type of the function
// are pure virtual.

class ViewGame {
	public:

		ViewGame() {}
		virtual ~ViewGame() {}

		// present the board
		virtual void printBoard(Board::ElementInBoard** board, int sizeOfBoard) const = 0;

		// message to switch turns
		virtual void messageForTurn (string curPlayer) const = 0;

		// message of possible moves
		virtual void messagePossibleMoves(const vector<Location>& possibleMoves) const = 0;

		// display the player's last move
		virtual void messagePlayerMove(Location pointToDisplay, string curPlayer) const = 0;

		// message who is the winner
		virtual void messageWinner(string winPlayer) const = 0;

		//show any type of message
		virtual void showMessage(string stringToShow) const = 0;

		//shows switcing turns message and waits for any key press
		virtual void messageSwitchTurns() const = 0;

		//gets move from outside user of game
		virtual Location getMoveFromUser() const = 0;

		/**
		 * Shows the options in the vector by option's index, and returns user's choice.
		 *
		 * Index 0 should be menu's title, and other indexes should hold the matching message for the option.
		 * Messages should fit the format: "To MESSAGE, press INDEX"
		 */
		virtual int presentMenu(const vector<string>& menuOpps) const = 0;
};

#endif /* VIEWGAME_H_ */
