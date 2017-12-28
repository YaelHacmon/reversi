#ifndef CLIENT_H_
#define CLIENT_H_

#include "Location.h"
#include <string>
#include <vector>

/**
 * Defines a client in a client-server pair, allowing for a remote game vs. a remote human player.
 * Protocol:
 * 		If a move has been made, move will be sent/read as 2 integers, first row then column.
 * 		If no move has been made, (-1) will be sent/read.
 * 		If server disconnects - (-2) will be returned from integer returning methods.
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
	 * @return - 0 if succeeded, -2 if server disconnected
	 */
	int sendMove(Location& move);

	/**
	 * Sends a message to the server saying player has no moves.
	 * Agreed flag is (-2), meaning player has no moves
	 *
	 * @return - 0 if succeeded, -2 if server disconnected
	 */
	int sendNoMoves();

	/**
	 * Sends a message to the server saying given game has ended (game is over).
	 *
	 * @return - 0 if succeeded, -2 if server disconnected
	 */
	int sendEndGame(std::string& name); //TODO

	/**
	 * Reads the next move of other player from the server.
	 * @return - location of the next move other player made,
	 * (-1,-1) if player had no moves, (-2,-2) if server disconnected, and (-3,-3) if other player disconnected
	 */
	Location acceptMove();

	/**
	 * Reads the color assigned to the local player from the server.
	 * @return 1 if local player is black, 2 if local player is white, -2 if server disconnected
	 */
	int acceptColor();

	/**
	 * Starts a new game with the given name
	 * @param name of new game
	 * @return 0 if succeeded, -1 if a game with given name already exists, -2 if server disconnected
	 */
	int startGame(const std::string& name);

	/**
	 * Returns a list of the existing games from
	 * @return list of the games with a single waiting player, a list with the empty string if non exist,
	 * 				 and an empty list if server disconnected
	 */
	std::vector<std::string> listGames();

	/**
	 * Joins the given game
	 * @param name of game to join from given games list
	 * @return 0 if succeeded, -2 if server disconnected
	 */
	int joinGame(std::string name);

private:
	const char *serverIP;
	int serverPort;
	int clientSocket;

	/**
	 * Reads a number from server
	 * @return number read if succeeded, -2 if server disconnected
	 */
	int readNumber();

	/**
	 * Sends the given number to server
	 * @param number to send
	 * @return 1 if succeeded, 0 if server disconnected
	 */
	int writeNumber(int number);

	/**
	 * Sends given string to server.
	 * @param s string to send
	 * @return 1 if succeeded, 0 if server disconnected
	 */
	int writeString(std::string s);

};


#endif /* CLIENT_H_ */
