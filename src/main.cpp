///*
// * Roni Fultheim, ID: 313465965
// *
// * main.cpp
// * Implementation of main function - runs program
// */

#include <iostream>
#include "../include/GameManager.h"
#include "../include/Player.h"
#include "../include/Board.h"
#include "../include/Menu.h"
#include "../include/ViewByConsole.h"
#include "../include/HumanPlayer.h"
#include "../include/StandardMoveLogic.h"
#include <string>

using namespace std;


int main() {
	//allocate menu, board, logic and view on stack - currently there is only one type of logic and view, no need to allocate dynamically
	Menu menuReversi;
	Board board;
	StandardMoveLogic ml;
	ViewByConsole view;

	//allocate dynamically due to using abstract base type
	//first player is always the human player and is black
	Player* player1 = new HumanPlayer("X",Board::BLACK);

	//start game - opening message
	view.showMessage("Welcome to Reversi!");

	//getting white player by user's choice from player options menu
	Player* player2 = menuReversi.getPlayerByUserChoice(view);

	//allocate game manager on stack, sending abstract types by pointer and actual types by reference
	GameManager game_manger(&view, board, player1, player2, &ml);

	// play game
	game_manger.playGame();

	//release memory
	delete player1;
	delete player2; //was allocated in menu, but must be released here

	//	return 0;
}
