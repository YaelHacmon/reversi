/*
 * Roni Fultheim, ID: 313465965
 * MoveLogic.h
 */

#ifndef MOVELOGIC_H_
#define MOVELOGIC_H_

#include "Board.h"
#include "Player.h"
#include "Location.h"

/**
 * This class is in charge of maintaining, checking and enforcing a game's rules for a move.
 * It makes sure that every move follows the game's chosen logic.
 * Abstract class, seeing as there can be different sets of rules for this game, with different logic.
 *
 * It does not contain any private members, and therefore can be used for handling more than one game.
 * This allows for loose coupling in the design.
 */
class MoveLogic {
	public:
		/**
		 * Constructor. Seeing as class has no members - c'tor has no parameters.
		 */
		MoveLogic();

		/**
		 * Virtual destructor.
		 */
		virtual ~MoveLogic();

		/**
		 * Plays the given move for the given player on given board, according to the logic decided.
		 * Changes must be made to board, so it cannot be constant.
		 * The rules for playing a move differ in each set of rules, and therefore this method is a
		 * pure virtual method, to be implemented in derived classes.
		 *
		 * @param move location of chosen move
		 * @param player pointer tp player playing move
		 * @param board pointer to board on which move is played
		 */
		virtual void playMove(const Location& move, const Player* player, Board* board) const = 0;

		/**
		 * Checks if given player can currently play a turn.
		 * A player can play if the list of player's next possible moves is not empty.
		 * Even so, a derived class may need a completely different implementation, and therefore it is still virtual.
		 *
		 * @param player pointer to player
		 * @return true if player can currently play a turn
		 */
		virtual bool canPlayTurn(const Player* player) const;

		/**
		 * Returns if a given move by a given player on given board is allowed.
		 * A move is allowed if it is a possible move, meaning it is contained
		 * in the player's possible moves vector.
		 *
		 * @param move location of move to check if legal
		 * @param player pointer to player playing this move
		 * @return true if move is legal and can be played
		 */
		virtual bool isMoveAllowed(const Location& move, const Player* player) const;

		/**
		 * Updates the list of possible moves for the given player on the given board.
		 * 	Change must be made to actual player, so it is not constant.
		 * Depends on the set of rules chosen for the game, and therefore uses a template pattern in the implementation,
		 * using possibleMoveDirections pure virtual method.
		 * Even so, a derived class may need a completely different implementation, and therefore it is still virtual.
		 *
		 * @param player pointer to player of which to update moves
		 * @param board pointer to board on which game is played
		 */
		virtual void updateMoveOptions(Player* player, const Board* board) const;

	protected:
		/**
		 * Checks if a given location can be a possible move by this logic's rules.
		 * Is pure virual because depends on the specific implemetation of MoveLogic.
		 *
		 * @param color to make given cell location
		 * @param location of cell
		 * @param board pointer to board on which move is to be played
		 */
		virtual bool isPossibleMoveByLogic(Player::ColorOfPlayer color, Location& location, const Board* board) const = 0;


		/**
		 * Checks if given move is an option for given player to make on the given board in all 8 directions,
		 * and if so - saves location of last square in opposite-colored range to the passed Locations array.
		 * Depends on the set of rules applied, so must be implemented only in derived classes.
		 *
		 * @param dirs array of 8 locations, initialized to checked move option location
		 * @param player pointer to player making the move
		 * @param board pointer to board on which move is to be played
		 */
		virtual void possibleMoveDirections(Location* dirs, const Player* player, const Board* board) const = 0;

		/**
		 * Returns the location of the last square in a range of consecutive same-colored squares.
		 *
		 * Method looks for the first square in the given board that does not match the color of the given start location,
		 * up to the given end location. If such a square is found before reaching the end - it's location is returned.
		 * Otherwise, the last found square's location is returned.
		 * The squares are checked in the specified differences, which allowes for traversing rows, columns and
		 * diagonals in all directions.
		 *
		 * @param prevStart location of square before start of inquiry range
		 * @param end  edge of board - end of inquiry range
		 * @param board  pointer to board in which we are searching for the range
		 * @param pColor color of played move - color to be in given prevStart location
		 * @return location of the next first square in the given board and range that matches the prevStart
		 * 				 square's color, or if none are found - the location of prevStart.
		 */
		Location lastInColorRange(const Player::ColorOfPlayer pColor, const Location& prevStart,
				const Location& end, const Board* board) const;


		/**
		 * Determines the jump differences in a range of rows/columns for current iteration over board.
		 * In the Reversi game, we examine a the board one square at a time (jumps of 1). Therefore some location down
		 * the wanted iterating range is enough to determine the direction of this iteration, and return the jump difference.
		 *
		 * Even so, a derived logic class may decide to act differently, so method is declared virtual.
		 *
		 * @param start start of iteration range
		 * @param next some location down the iteration range
		 * @return -1, 0, or 1: difference in rows/columns in this iteration
		 */
		virtual int jumps(const int start, const int someNext) const;
};


#endif /* MOVELOGIC_H_ */
