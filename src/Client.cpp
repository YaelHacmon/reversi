/*
 * Client.cpp
 */

#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
using namespace std;


Client::Client(const char *serverIP, int serverPort):
		serverIP(serverIP), serverPort(serverPort),
		clientSocket(0) {
	cout << "Client" << endl;
}


void Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}
	// Convert the ip string to a network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address";
	}

	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof
			address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}
	// Create a structure for the server address
	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));
	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char
			*)server->h_addr, server->h_length);
	// htons converts values between host and network byte orders
	serverAddress.sin_port = htons(serverPort);
	// Establish a connection with the TCP server
	if (connect(clientSocket, (struct sockaddr
			*)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
	cout << "Connected to server" << endl;
}


void Client::sendMove(Location move) {
	//send row of move
	int n = write(clientSocket, &move.row(), sizeof(move.row()));
	if (n == -1) {
		throw "Error writing row to socket";
	}

	//send column of move
	int n = write(clientSocket, &move.column(), sizeof(move.column()));
	if (n == -1) {
		throw "Error writing column to socket";
	}
}


void Client::sendNoMoves() {
	//TODO - ok this way or should just write (-1) in function?
	int noMoves = -1;
	//send (-1), signal of no moves
	int n = write(clientSocket, &noMoves, sizeof(noMoves));
	if (n == -1) {
		throw "Error writing 'no moves' signal to socket";
	}
}


void Client::sendEndGame() {
	//TODO - ok this way or should just write (-1) in function?
	int endGame = -2;
	//send (-2), signal of end of game
	int n = write(clientSocket, &endGame, sizeof(endGame));
	if (n == -1) {
		throw "Error writing 'no moves' signal to socket";
	}
}


Location Client::acceptMove() {
	// Read the row of move from the server
	int row;
	int n = read(clientSocket, &row, sizeof(row));
	if (n == -1) {
		throw "Error reading row of move from socket";
	}

	// if other player had no moves - player will send (-1)
	if (row == -1) {
		return Location(-1,-1);
	}

	// Read the column of move from the server
	int column;
	n = read(clientSocket, &column, sizeof(column));
	if (n == -1) {
		throw "Error reading column of move from socket";
	}

	//return a copy - since allocated on stack
	return Location(row, column);
}


