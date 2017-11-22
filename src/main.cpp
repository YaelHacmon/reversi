/*
 * Roni Fultheim, ID: 313465965
 *
 * main.cpp
 * Implementation of main function - runs program
 */

#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "Board.h"
#include "Menu.h"
#include "ViewByConsole.h"
#include "HumanPlayer.h"
#include "StandardMoveLogic.h"
#include <string>

using namespace std;


int main() {

	// allocate menu on stack
	Menu menuReversi;


	// allocate logic and view on stack - currently there is only one type of logic and view, no need to allocate dynamically
	StandardMoveLogic ml;
	ViewByConsole view;

	Board board;

	// first player is always the human player and is black
	Player* player1 = new HumanPlayer("X",Board::BLACK);

	//start game - opening message
	view.showMessage("Welcome to Reversi!");

	//getting white player by user's choice from player options menu
	Player* player2 = menuReversi.getPlayerByUserChoice(view);

	GameManager game_manger(&view, &board, player1, player2, &ml);

	// play game
	game_manger.playGame();

	//release memory
	delete player1;
	delete player2; //was allocated in menu, but must be released here

	return 0;
}
