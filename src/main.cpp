/*
 * Roni Fultheim, ID: 313465965
 *
 * main.cpp
 * Implementation of main function - runs program
 */

#include <iostream>
#include "GameManager.h"
#include "Player.h"
#include "ViewByConsole.h"
#include "HumanPlayer.h"
#include "StandardMoveLogic.h"
#include "Board.h"
#include <string>
#include <Menu.h>

using namespace std;


int main() {

/*	// initialize game
	cout << "Welcome to Reversi!" << endl;*/

	// allocate on stack
	// currently there is only one type of logic
	// no need to allocate dynamically
	Menu menuReversi;

	ViewByConsole view;

	StandardMoveLogic ml;

	Board board;

	// the first black player is always the human player
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
