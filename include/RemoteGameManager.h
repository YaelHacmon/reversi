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
	std::string name_; //name of game

	/**
	 * Plays the turn of the local player.
	 * Specifically, asks player for move and sends it to the server.
	 * 	 * @return true if game continues, false otherwise
	 */
	bool playLocalTurn();

	/**
	 * Plays the turn of the remote player.
	 * Specifically, gets move from server and plays it on board
	 * @return true if game continues, false otherwise
	 */
	bool playRemoteTurn();

	/**
	 * Sets up the game - connects client to server,
	 * asks player to start or join a game, contacts server with request, etc.
	 * @return true if game was set up correctly, false otherwise
	 */
	bool setup();

	/**
	 * Shows message of end of game to user and waits for any input.
	 */
	void serverDisconnected();
};


#endif /* REMOTEGAMEMANAGER_H_ */
