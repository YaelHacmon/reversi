/*
 * Roni Fultheim, ID: 313465965
 * HumanPlayer.h
 */

#ifndef HumanPlayer_H_
#define HumanPlayer_H_

#include "Player.h"


/**
 * Represents a human player in a game played via the console.
 */
class HumanPlayer: public Player {
public:
	/**
	 * Constructor of HumanPlayer. Name and color must be given.
	 *
	 * @param name player's name
	 * @param c player's color
	 */
	HumanPlayer(const std::string& name, const Player::ColorOfPlayer& c): Player(name, c){};

	/**
	 * Copy c'tor. Calls base's copy c'tor and updates possible moves
	 * @param player to copy
	 */
	HumanPlayer(const Player& other): Player(other) {};

	/**
	 * implement clone function for making copy of Player object
	 * of any type. use clone because Player have derived classes.
	 */
	virtual Player* clone() const;

	/**
	 * Returns human player's next move in game, by asking user to enter their choice.
	 *
	 * @param v view to interact with player - accept input and make sure input is valid
	 * @param logic rules of current game
	 * @param b board on which game is being played
	 * @param other opponent
	 * @return location of next player's move
	 */
	virtual Location getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other);
};


#endif /* HumanPlayer_H_ */
