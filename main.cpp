/*
 * Roni Fultheim, ID: 313465965
 *
 * main.cpp
 * Implementation of main function - runs program
 */

#include <iostream>
#include "GameManager.h"
#include "HumanPlayer.h"
#include "StandardMoveLogic.h"
#include <string>

using namespace std;


/**
 * Creates a Board initialized by default parameters and prints it
 */
int main() {
	//initialize game
	cout << "Welcome to Reversi!" << endl;

	//dynamically allocate objects of general types on heap
	Player* player1 = new HumanPlayer("X",Board::BLACK);
	Player* player2 = new HumanPlayer("O",Board::WHITE);

	//allocate on stack
	//currently there is only one type of logic - no need to allocate dynamically
	StandardMoveLogic ml;
	ViewByConsole view;
	Board board;
	GameManager gf(&view,&board,player1, player2, &ml);

	//play game
	gf.playGame();

	//release memory
	delete player1;
	delete player2;


	return 0;
}
