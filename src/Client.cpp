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

#define MAX_COMMAND_LENGTH 60
//set maximal string length (for list_games command) to 1024 bytes (1 kb)
#define MAX_STRING_LENGTH 1024
//TODO - is this okay/enough? -> at least 20 games (longest string sent and recieved)

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


int Client::sendMove(Location& move) {
	//send command - "play", check for error (=0)
	if (!writeString("play")) {
		//if server disconnected - return -2
		return -2;
	}


	//send row of move - check for error (=0)
	if (!writeNumber(move.row())) {
		//if server disconnected - return -2
		return -2;
	}

	//send column of move - check for error (=0)
	if (!writeNumber(move.column())) {
		//if server disconnected - return -2
		return -2;
	}

	//method ended successfully - return 0
	return 0;
}


int Client::sendNoMoves() {
	//send command - "play", check for error (=0)
	if (!writeString("play")) {
		//if server disconnected - return -2
		return -2;
	}

	//send flag for no moves - (-2), and check for error (=0)
	if (!writeNumber(-2)) {
		//if server disconnected - return -2
		return -2;
	}

	//method ended successfully - return 0
	return 0;
}


int Client::sendEndGame(string& name) {
	//create command, of format "close <name>"
	string command = "close " + name;

	//send command, check for error (=0)
	if (!writeString(command)) {
		//if server disconnected - return -2
		return -2;
	}

	//method ended successfully - return 0
	return 0;
}


Location Client::acceptMove() {
	// Read the row of move from the server
	int row;
	int n = read(clientSocket, &row, sizeof(row));

	if (n == -1) {
		throw "Error reading row of move from socket";
	} else if (n==0) {
		//read nothing - server disconnected - return (-2,-2)
		return Location(-2, -2);
	}

	// if other player had no moves - player will send (-1)
	if (row == -1) {
		return Location(-1,-1);
	}

	//if other player has disconnected, server will send (-3)
	if (row == -3) {
		return Location(-3, -3);
	}

	// Read the column of move from the server
	int column;
	n = read(clientSocket, &column, sizeof(column));
	if (n == -1) {
		throw "Error reading column of move from socket";
	} else if (n==0) {
		//read nothing - server disconnected - return (-2,-2)
		return Location(-2, -2);
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
	} else if (n==0) {
		//if server disconnected - return -2
		return -2;
	}

	//else - return color
	return color;
}


int Client::writeNumber(int number) {
	//write number to server
	int n = write(clientSocket, &number, sizeof(number));
	if (n == -1) {
		//if an error occurred - throw exception
		throw "Error writing column to socket";
	} else if (n==0) {
		//if server disconnected - return 0
		return 0;
	}

	//else - method ended successfully, return 1
	return 1;
}


int Client::writeString(std::string s) {
	//TODO - is it right to resize each time?
	//resize to maximal sent string size
	s.resize(MAX_COMMAND_LENGTH);

	//write number to opponent
	int n = write(clientSocket, &s, MAX_STRING_LENGTH);
	if (n == -1) {
		//if an error occurred - throw exception
		throw "Error writing column to socket";
	} else if (n==0) {
		//if server disconnected - return 0
		return 0;
	}

	//else - method ended successfully, return 1
	return 1;

}
