/*
 * Roni Fultheim, ID: 313465965
 * StandardMoveLogic.h
 */

#ifndef STANDARDMOVELOGIC_H_
#define STANDARDMOVELOGIC_H_

#include "MoveLogic.h"

/**
 * Represent the standard move logic of a Reversi game.
 * A move is allowed only if it changes square colors, and square colors are changed if the new
 * move blocks a range of squares with the opposite color between move and a same-colored square.
 */
class StandardMoveLogic: public MoveLogic {
	public:
		/**
		 * Plays the given move for the given player on given board, according to the logic decided.
		 * Changes must be made to board, so it cannot be constant.
		 * Derived from parent class, originally a pure virtual method.
		 *
		 * Plays a move by switching the color of all consequent same-colored squares from given move.
		 *
		 * @param move location of chosen move
		 * @param player pointer to player playing move
		 * @param board pointer to board on which move is played
		 */
		virtual void playMove(const Location& move, const Player* player, Board* board) const;


		/**
		 * Returns if a given move by a given player on given board is allowed.
		 * Derived from parent class, originally a pure virtual method.
		 *
		 * A move is allowed if it causes at least one other square to change color.
		 *
		 * @param move location of move to check if legal
		 * @param player pointer to player playing this move
		 * @param board pointer to  board on which move is played
		 * @return true if move is legal and can be played
		 */
		virtual bool isMoveAllowed(const Location& move, const Player* player, const Board* board) const;

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
		 * Checks if given move is an option for given player to make on the given board,
		 * and if so - saves location of last square in opposite-colored range to the passed Locations array.
		 *
		 * In the standard rules, a direction can be possible for a move if it has at least one neightboring
		 * square with opposite color, and if opposite colored square range is flanked by a square with same
		 * color as move's.
		 *
		 * @param dirs array of 8 locations, initialized to checked move option location
		 * @param pColor color of to player making the move
		 * @param board pointer to board on which move is to be played
		 */
		virtual void possibleMoveDirections(Location* dirs, const Player::ColorOfPlayer pColor, const Board* board) const;
};



#endif /* STANDARDMOVELOGIC_H_ */
