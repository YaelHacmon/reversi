/*
 * ViewByConsole.h
 *
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#ifndef VIEWBYCONSOLE_H_
#define VIEWBYCONSOLE_H_
#include "ViewGame.h"

class ViewByConsole : public ViewGame
{
public:

	ViewByConsole() {}
	~ViewByConsole() {}
	// present the board
	virtual void printBoard(Board::ElementInBoard** board, int sizeOfBoard) const;

	// message to switch turns
	virtual void messageForTurn (string curPlayer) const;

	// message of possible moves
	virtual void messagePossibleMoves(vector<Location> &possibleMoves) const;

	// display the player's last move
	virtual void messagePlayerMove(Location pointToDisplay, string curPlayer) const;

	// message who is the winner
	virtual void messageWinner(string winPlayer) const;

	//show any type of message
	virtual void showMessage(string stringToShow) const;

	//shows switcing turns message and waits for any key press
	virtual void messageSwitchTurns() const;

	//gets move from outside user of game
	virtual Location getMoveFromUser() const;

	/**
	 * Shows the options in the vector by option's index, and returns user's choice.
	 *
	 * Index 0 should be menu's title, and other indexes should hold the matching message for the option.
	 * Messages should fit the format: "To MESSAGE, press INDEX"
	 */
	virtual int presentMenu(const vector<string>& menuOpps) const;
};
#endif /* VIEWBYCONSOLE_H_ */
