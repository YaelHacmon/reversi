/*
 * ReversiGame.cpp
 *
 *  313297897
 *  Author: Yael Hacmon
 */

#include "ReversiGame.h"
#include <iostream>
using namespace std;


void  ReversiGame::buildVectorByMoves(vector<Point>& possibleMoves) const
{

	for(list<Point>::const_iterator iter = board_game.emptyCellsBegin();
			iter != board_game.emptyCellsEnd(); ++iter)
	{
		fillVectorByPoint(possibleMoves, *iter);
	}
}

void ReversiGame::fillVectorByPoint(vector<Point>& possibleMoves, Point isValidPoint) const
{
	if (checkRight(isValidPoint)
			|| checkUp(isValidPoint)
			|| checkUpRight(isValidPoint)
			|| checkRightDown(isValidPoint)
			|| checkDown(isValidPoint)
			|| checkLeftDown(isValidPoint)
			|| checkLeft(isValidPoint)
			|| checkUpLeft(isValidPoint))
	{
		possibleMoves.push_back(isValidPoint);
	}
}

bool ReversiGame::checkUp(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();
	if(row -2 >= 0)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row-1, col)
				&& current_player->getColor() == board_game.getElementInBoard(row-2, col))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkUpRight(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();
	int sizeOfBoard = board_game.getSize();

	if(row -2 >= 0 && col + 2 < sizeOfBoard)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row-1, col+1)
				&& current_player->getColor() == board_game.getElementInBoard(row-2, col+2))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkRight(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();
	int sizeOfBoard = board_game.getSize();

	if(col + 2 < sizeOfBoard)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row, col+1)
				&& current_player->getColor() == board_game.getElementInBoard(row, col+2))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkRightDown(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();
	int sizeOfBoard = board_game.getSize();

	if(row + 2 < sizeOfBoard && col + 2 < sizeOfBoard)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row+1, col+1)
				&& current_player->getColor() == board_game.getElementInBoard(row+2, col+2))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkDown(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();
	int sizeOfBoard = board_game.getSize();

	if(row + 2 < sizeOfBoard)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row+1, col)
				&& current_player->getColor() == board_game.getElementInBoard(row+2, col))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkLeftDown(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();
	int sizeOfBoard = board_game.getSize();

	if(row +2 < sizeOfBoard && col - 2 >= 0)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row+1, col-1)
				&& current_player->getColor() == board_game.getElementInBoard(row+2, col-2))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkLeft(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();

	if(col -2 >= 0)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row, col-1)
				&& current_player->getColor() == board_game.getElementInBoard(row, col-2))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}
bool ReversiGame::checkUpLeft(Point isValidPoint) const
{
	int row = isValidPoint.getX();
	int col = isValidPoint.getY();

	if(row -2 >= 0 && col -2 >= 0)
	{
		if(current_player->getOppColor() == board_game.getElementInBoard(row-1, col-1)
				&& current_player->getColor() == board_game.getElementInBoard(row-2, col-2))
		{
			// a valid point - add to the vector of the possible options
			return true;
		}
	}
	return false;
}


// make the final updates of the player step
void ReversiGame::finishSteps(int incScores, int decScores) const
{
	current_player->increaseScore(incScores);
	opp_player->decreaseScore(decScores);
}

//update the board according to the choice of the player
void ReversiGame::moveInBoard(Point pointToChange)
{
	int row = pointToChange.getX();
	int col = pointToChange.getY();
	int scores = 0;
	Player::ColourOfPlayer currColour = current_player->getColor();

	board_game.setElementInBoard(currColour, row, col);
	board_game.romoveCellFromEmptyList(pointToChange);

	if(checkUp(pointToChange))
	{
		board_game.setElementInBoard(currColour, row-1, col);
		++scores;
	}
	if(checkUpRight(pointToChange))
	{
		board_game.setElementInBoard(currColour, row-1, col+1);
		++scores;
	}
	if(checkRight(pointToChange))
	{
		board_game.setElementInBoard(currColour, row, col+1);
		++scores;
	}

	if(checkRightDown(pointToChange))
	{
		board_game.setElementInBoard(currColour, row+1, col+1);
		++scores;
	}
	if(checkDown(pointToChange))
	{
		board_game.setElementInBoard(currColour, row+1, col);
		++scores;
	}
	if(checkLeftDown(pointToChange))
	{
		board_game.setElementInBoard(currColour, row+1, col-1);
		++scores;
	}
	if(checkLeft(pointToChange))
	{
		board_game.setElementInBoard(currColour, row, col-1);
		++scores;
	}
	if(checkUpLeft(pointToChange))
	{
		board_game.setElementInBoard(currColour, row-1, col-1);
		++scores;
	}
	finishSteps(scores+1, scores);
	//TODO
	cout<<"score " << current_player->strColor() << " : " << current_player->gerScore() << endl;
	cout<< "score "<< opp_player->strColor() << " : "<< opp_player->gerScore()<<endl;
}
// check who is the winner of the game according to the scores
void ReversiGame::messageWin() const
{
	if(current_player->gerScore() > opp_player->gerScore())
	{
		view->messageWinner(current_player);
	}
	else if(opp_player->gerScore() > current_player->gerScore())
	{
		view->messageWinner(opp_player);
	}
	else
	{
		view->messageTiko();
	}
}
