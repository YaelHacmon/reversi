/*
 * Client.h
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include "Location.h"

/**
 * Defines a client in a client-server pair, allowing for a remote game vs. a remote human player.
 * Protocol:
 * 		If a move has been made, move will be sent/read as 2 integers, first row then column.
 * 		If no move has been made, (-1) will be sent/read.
 * 		If game is over, (-2) will be sent to server.
 */
class Client {
public:
	/**
	 * Default c'tor, in our implementation it will read the server's IP and port from a configuration file and then call
	 * non-default c'tor
	 */
	Client();

	/**
	 * Connects to the server.
	 */
	void connectToServer();

	/**
	 * Sends last player's move to server.
	 * @param move - location of last move to send
	 */
	void sendMove(Location move);

	/**
	 * Sends a message to the server saying player has no moves.
	 */
	void sendNoMoves();

	/**
	 * Sends a message to the server saying game has ended (game is over).
	 */
	void sendEndGame();

	/**
	 * Reads the next move of other player from the server.
	 * @return - location of the next move other player made, (-1,-1) if player had no moves, (-2,-2) if other player disconnected
	 */
	Location acceptMove();

	/**
	 * Reads the color assigned to the local player from the server.
	 * @return - 1 if local player is black, 2 if local player is white
	 */
	int acceptColor();

private:
	const char *serverIP;
	int serverPort;
	int clientSocket;
};


#endif /* CLIENT_H_ */
