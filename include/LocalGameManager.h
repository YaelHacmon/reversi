/*
 * LocalGameManager.h
 */

#ifndef LOCALGAMEMANAGER_H_
#define LOCALGAMEMANAGER_H_

#include "GameManager.h"

/**
 * Manages a game that is played on one machine (locally).
 */
class LocalGameManager: public GameManager {
public:
	/**
	 * Constructor taking a board on which to play game, two players, and the logic of the moves.
	 * @param b board of game
	 * @param black black player
	 * @param white white player
	 * @param log logic to handle moves
	 */
	LocalGameManager(ViewGame* view, Board& b, Player* black, Player* white, MoveLogic* log);

	/**
	 * Plays game with the given board, players and logic.
	 * Does so locally - interacts with players on the same machine.
	 */
	virtual void playGame();
};


#endif /* LOCALGAMEMANAGER_H_ */
