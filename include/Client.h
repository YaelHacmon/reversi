/*
 * Client.h
 */

#ifndef CLIENT_H_
#define CLIENT_H_

/**
 * Defines a client in a client-server pair, allowing for a remote game vs. a remote human player.
 * Protocol:
 * 		If a move has been made, move will be sent/read as 2 integers, first row then column.
 * 		If no move has been made, (-1) will be sent/read.
 * 		If game is over, (-2) will be sent to server.
 */
class Client {
public:
	//TODO - comments
	/**
	 * C'tor taking the
	 * @param
	 */
	Client(const char *serverIP, int serverPort);

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
	 * Sends a message to the server saying player has no moves.
	 */
	void sendNoMove();

	/**
	 * Sends a message to the server saying game has ended (game is over).
	 */
	void sendEndGame();

	/**
	 * Reads the next move of other player from the server.
	 * @return - location of the next move other player made, (-1,-1) if player had no moves
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
