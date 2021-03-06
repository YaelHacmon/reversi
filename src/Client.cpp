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
#include <iterator> //for istream_iterator
#include <sstream> //for istringstream

#define MAX_COMMAND_LENGTH 60
//set maximal string length (for list_games command) to 1024 bytes (1 kb)
#define MAX_STRING_LENGTH 1024

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
	serverIP = ip; //get char pointer array from string
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
	if (!inet_aton(serverIP.c_str(), &address)) {
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
	string command = "close " + name + '\0';

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
	int row = readNumber();

	// if other player had no moves - player will send (-1)
	if (row == -1) {
		return Location(-1,-1);
	}

	//if server disconnected, method will return (-2)
	if (row == -2) {
		return Location(-2, -2);
	}

	//if other player has disconnected, server will send (-3)
	if (row == -3) {
		return Location(-3, -3);
	}


	// else - Read the column of move from the server
	int column = readNumber();

	//if server disconnected, method will return (-2)
	if (row == -2) {
		return Location(-2, -2);
	}

	//if other player has disconnected, server will send (-3)
	if (row == -3) {
		return Location(-3, -3);
	}

	//else, return the read location
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


int Client::startGame(const std::string& name) {
	//create command, of format "start <name>"
	string command = "start " + name + '\0';

	//send command, check for error (=0)
	if (!writeString(command)) {
		//if server disconnected - return -2
		return -2;
	}

	//otherwise - read number from server, protocol: -1 if such a game exists, 0 if initialization was successful
	//just return read number - 0 for success, (-1) for failure, and method returns (-2) if server disconnected
	int num = readNumber();
	return num;
}


vector<string> Client::listGames() {
		//create command, of format "list_games"
	string command = "list_games";

	//send command, check for error (=0)
	if (!writeString(command)) {
		//if server disconnected - return an empty list
		return vector<string>();
	}

	//else - read the string with list of waiting games
	char connectedList[MAX_STRING_LENGTH];

	int n = read(clientSocket, connectedList, MAX_STRING_LENGTH);
	if (n == -1) {
		throw "Error reading number from socket";
	} else if (n==0) {
		//if server disconnected - return an empty list
		return vector<string>();
	}

	string temp(connectedList);

	//if the empty string was read - return list with the empty string
	if (temp == "") {
		vector<string> vec;
		vec.push_back("");
		return vec;
	}

	//otherwise - split the read string
	istringstream iss(temp);
	vector<string> list((istream_iterator<string>(iss)), istream_iterator<string>());

	//return list
	return list;
}


int Client::joinGame(string name) {
	//ask client to reconnect with server (after stopping connection when ending start\list_games commands)
	try {
		connectToServer();
	} catch (const char *msg) {
		std::cout << "Failed to connect to server. Reason: " << msg << std::endl;
		exit(-1);
	}

	//create command, of format "start <name>"
	string command = "join " + name + '\0';

	//send command, check for error (=0)
	if (!writeString(command)) {
		//if server disconnected - return -2
		return -2;
	}

	//otherwise - joining was successful, return 0
	return 0;
}


int Client::readNumber() {
	int num;
	int n = read(clientSocket, &num, sizeof(num));
	if (n == -1) {
		throw "Error reading number from socket";
	} else if (n==0) {
		//if server disconnected - return -2
		return -2;
	}

	//else - method ended successfully, return read number
	return num;
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
	char str[MAX_COMMAND_LENGTH];
	strncpy(str,s.c_str(),MAX_COMMAND_LENGTH);

	//write number to opponent
	int n = write(clientSocket, str, MAX_COMMAND_LENGTH);

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
