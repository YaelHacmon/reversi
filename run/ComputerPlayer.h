
#ifndef ComputerPlayer_H_
#define ComputerPlayer_H_

#include "Player.h"

/**
 * Represents a computer player in a game.
 */
class ComputerPlayer: public Player
{
public:
	/**
	 * Constructor of ComputerPlayer. Name and color must be given.
	 *
	 * @param name player's name
	 * @param c player's color
	 */
	ComputerPlayer(const std::string& name, const Player::ColorOfPlayer& c): Player(name, c){};

	/**
	 * Copy c'tor. Calls base's copy c'tor and updates possible moves
	 * @param player to copy
	 */
	ComputerPlayer(const Player& other): Player(other) {updatePossibleMoves(other.getPossibleMoves());};

	/**
	 * Returns player's next move in game by minimax algorithem
	 *
	 * @param v view to interact with player - accept input and make sure input is valid
	 * @param logic rules of current game
	 * @param b board on which game is being played
	 * @param current current player
	 * @param other opponent player
	 *
	 * @return location of next player's move
	 */
	Location getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other);

	Player* clone() const;
};



#endif /* ComputerPlayer_H_ */
