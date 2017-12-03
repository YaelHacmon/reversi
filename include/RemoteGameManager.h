/*
 * RemoteGameManager.h
 */

#ifndef REMOTEGAMEMANAGER_H_
#define REMOTEGAMEMANAGER_H_

#include "GameManager.h"
#include "Client.h"

/**
 * Manages a game that is played via a server (remotely).
 */
class RemoteGameManager: public GameManager {
public:
	/**
	 * Constructor taking a board on which to play game, two players, and the logic of the moves.
	 * @param b board of game
	 * @param black black player
	 * @param white white player
	 * @param log logic to handle moves
	 */
	RemoteGameManager(ViewGame* view, Board& b, Player* black, Player* white, MoveLogic* log);

	/**
	 * Plays game with the given board, players and logic.
	 */
	virtual void playGame();

private:
	Client client_;

	/**
	 * Plays the turn of the local player.
	 * Specifically, asks player for move and sends it to the server.
	 * 	 * @return true if game continue, false otherwise
	 */
	bool playLocalTurn();

	/**
	 * Plays the turn of the remote player.
	 * Specifically, gets move from server and plays it on board
	 * @return true if game continue, false otherwise
	 */
	bool playRemoteTurn();
};


#endif /* REMOTEGAMEMANAGER_H_ */
