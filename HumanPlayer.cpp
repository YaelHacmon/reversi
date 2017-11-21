/*
 * Roni Fultheim, ID: 313465965
 * HumanPlayer.cpp
 */


#include <iostream>
#include <limits>
#include "MoveLogic.h"
#include "HumanPlayer.h"

using namespace std;


Location HumanPlayer::getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other)
{
	//sk for move
	view->showMessage("Please enter your moves row,col:");

	//reurn choice of move
	return view->getMoveFromUser();
}
