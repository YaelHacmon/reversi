/*
 * Client.cpp
 */

#include "../include/Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h> //for exit(1), for atoi()

using namespace std;

Client::Client(): clientSocket(0) {
	ifstream config;
	config.open("reversi_config.txt", std::fstream::in);

	if (!config) {
	    cerr << "Unable to open Client configuration file";
	    exit(1);   // call system to stop
	}

	//read server IP then server's port from the configuration file
	string ip, port;
	config >> ip >> port;

	//close file
	config.close();

	//assign server port and IP
	serverIP = ip.c_str(); //get char pointer array from string
	serverPort = atoi(port.c_str()); 	//translate port number to integer
}

void Client::connectToServer() {
	// Create a socket point
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1) {
		throw "Error opening socket";
	}

	// Convert the IP string to a network address
	struct in_addr address;
	if (!inet_aton(serverIP, &address)) {
		throw "Can't parse IP address";
	}

	// Get a hostent structure for the given host address
	struct hostent *server;
	server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
	if (server == NULL) {
		throw "Host is unreachable";
	}

	// Create a structure for the server address
	struct sockaddr_in serverAddress;
	bzero((char *)&address, sizeof(address));
	serverAddress.sin_family = AF_INET;
	memcpy((char *)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);

	// htons converts values between host and network byte orders
	serverAddress.sin_port = htons(serverPort);

	// Establish a connection with the TCP server
	if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error connecting to server";
	}
}


void Client::sendMove(Location move) {
	//send row of move
	int row = move.row();
	int n = write(clientSocket, &row, sizeof(row));
	if (n == -1) {
		throw "Error writing row to socket";
	}

	//send column of move
	int col = move.column();
	n = write(clientSocket, &col, sizeof(col));
	if (n == -1) {
		throw "Error writing column to socket";
	}
}


void Client::sendNoMoves() {
	int noMoves = -1;
	//send (-1), signal of no moves
	int n = write(clientSocket, &noMoves, sizeof(noMoves));
	if (n == -1) {
		throw "Error writing 'no moves' signal to socket";
	}
}


void Client::sendEndGame() {
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
	} else if (n==0) {
		//read nothing - other player disconnected
		return Location(-2, -2);
	}

	// if other player had no moves - player will send (-1)
	if (row == -1) {
		return Location(-1,-1);
	}

	//if other player has disconnected, server will send (-3)
	if (row == -3) {
		return Location(-2, -2);
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


int Client::acceptColor() {
	// Read the integer representing the color of local player (1=black, 2=white) from the server
	// read waits for message to be sent by the server
	int color;
	int n = read(clientSocket, &color, sizeof(color));
	if (n == -1) {
		throw "Error reading row of move from socket";
	}
	//return it
	return color;
}
