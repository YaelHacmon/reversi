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
#include <Menu.h>

using namespace std;


int main() {

	// initialize game
	cout << "Welcome to Reversi!" << endl;

	// allocate on stack
	// currently there is only one type of logic
	// no need to allocate dynamically
	Menu menuReversi;

	//RONI - fix "abs" in MoveLogic::playMove
	StandardMoveLogic ml;

	ViewByConsole view;
	Board board;

	// the first black player is always the human player
	Player* player1 = new HumanPlayer("X",Board::BLACK);

	// getting white player by user's choice
	Player* player2 = menuReversi.getPlayerByUserChoice(view);


	GameManager game_manger(&view,&board,player1, player2, &ml);

	// play game
	game_manger.playGame();

	//release memory
	delete player1;
	delete player2;
	return 0;
}
