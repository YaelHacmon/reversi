
#ifndef ComputerPlayer_H_
#define ComputerPlayer_H_

#include "Player.h"

/**
 * Represents a computer player in a game.
 */
class ComputerPlayer: public Player
{
public:

	ComputerPlayer(const std::string& name, const Player::ColorOfPlayer& c): Player(name, c){};

	ComputerPlayer(ComputerPlayer& other);

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
