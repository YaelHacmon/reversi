/*
 * Roni Fultheim, ID: 313465965
 * Yael Hacmon, ID: 313297897
 * HumanPlayer.cpp
 */


#include <iostream>
#include <limits>
#include "../include/MoveLogic.h"
#include "../include/HumanPlayer.h"

using namespace std;

Location HumanPlayer::getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other)
{
	//ask for move
	view->showMessage("Please enter your moves row,col:");

	//return choice of move
	return view->getMoveFromUser();
}

Player* HumanPlayer::clone() const
{
	return new HumanPlayer(*this);
}
