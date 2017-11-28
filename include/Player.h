
#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>
#include "Board.h"
#include "Location.h"
#include "ViewGame.h"

class MoveLogic;

/**
 * Repesenting a player in a Reversi game.
 * A player has a name and a color which represents him in the game.
 *
 * Abstract class, as there can be different types of players, which get their next moves in different ways.
 */
class Player {
public:
	typedef Board::ElementInBoard ColorOfPlayer;

	/**
	 * Constructor of Player. Name and color must be given.
	 *
	 * @param name player's name
	 * @param c player's color
	 */
	Player(const std::string& name, const ColorOfPlayer& c);

	/**
	 * Copy c'tor
	 * @param player to copy
	 */
	Player(const Player& other);

	/**
	 * Virtual destructor.
	 */
	virtual ~Player();

	/**
	 * implement clone function for making copy of Player object
	 * of any type. use clone because Player have derived classes.
	 */
	virtual Player* clone() const = 0;

	/**
	 * Returns player's next move in game. Is not constant, since getting next
	 * move can cause player's members to change.
	 *
	 * Pure virtual method that must be implemented in derived classes,
	 * since getting the next move depends on the player's type.
	 *
	 * @param v view to interact with player - accept input and make sure input is valid
	 * @param logic rules of current game
	 * @param b board on which game is being played
	 * @param other opponent
	 * @return location of next player's move
	 */
	virtual Location getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other) = 0;

	/**
	 * Returns the color representing this player in the game.
	 * @return player color in the game
	 */
	ColorOfPlayer getColor() const;

	/**
	 * Returns the player's name in the game.
	 *
	 * @return player's name in the game
	 */
	const std::string& getName() const;

	/**
	 * Returns score of player.
	 * @return current player's score
	 */
	int getScore() const;

	/**
	 * Return's the player's current possible moves, for examination only.
	 * By reference, to avoid copying, constant - to avoid change.
	 *
	 * @return locations where the player could place a square with his color
	 */
	const std::vector<Location>& getPossibleMoves() const;

	/**
	 * Checks if player has possible moves to make.
	 *
	 * @return locations where the player could place a square with his color
	 */
	bool hasPossibleMoves() const;

	/**
	 * Updates the current locations where the player can make his next move to a new vector of possible moves.
	 * Keeping the vector constant ensures that it will be copied.
	 *
	 * @param locs vector of new possible moves
	 */
	void updatePossibleMoves(const std::vector<Location>& locs);

	/**
	 * Decrease player's score by given amount.
	 * @param toDecrease number of points to decrease.
	 */
	void decreaseScore (int toDecrease);

	/**
	 * Increase player's score by given amount.
	 * @param toIncrease number of points to increase.
	 */
	void increaseScore (int toIncrease);

protected:
	// name of player, cannot be changed during game
	const std::string name_;
	// color of player in the game, cannot be changed during game
	const Player::ColorOfPlayer color_;
	//current score of player (number of cells with player's color
	int score_;
	//vector of currently possible moves to be made by the player
	std::vector<Location> possibleMoves_;
};


#endif /* PLAYER_H_ */
