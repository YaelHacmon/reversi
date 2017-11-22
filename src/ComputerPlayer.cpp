/*
 * Roni Fultheim, ID: 313465965
 * Yael Hacmon, ID: 313297897
 * ComputerPlayer.cpp
 */
#include <iostream>
#include <limits>
#include "MoveLogic.h"
#include "ComputerPlayer.h"
#include <vector>

using namespace std;


Player* ComputerPlayer::clone() const
{
	return new ComputerPlayer(*this);
}

//according to minimax algorithm
Location ComputerPlayer::getNextMove(const ViewGame* view, const MoveLogic* logic, const Board* board,const Player* current ,const Player* other)
{

	int minimax = numeric_limits<int>::infinity();

	int maxScore = 0;

	Location bestMove(-1,-1);

	Player* copyOther = other->clone();

	vector<Location> possiblCurrenteMoves = current->getPossibleMoves();
	vector<Location> possiblOtherMoves = copyOther->getPossibleMoves();

	// if the opp player have no possible moves,
	//it will return the first possible move.
	if(possiblOtherMoves.size() == 0){
		return  possiblCurrenteMoves[0];
	}

	else {
		//for each of the computer player possible move
		for(int m =0; m < possiblCurrenteMoves.size; ++m){
			Board copyBoard(board);

			//play move for the current player
			logic-> playMove(possiblCurrenteMoves[m],current,copyBoard,copyOther);

			//update the possible moves for the opponent player
			logic-> updateMoveOptions(copyOther,copyBoard);


			for(int i = 0; i < possiblOtherMoves.size; ++i){

				Board secondCopyBoard(copyBoard);

				//play the possible move
				logic-> playMove(possiblOtherMoves[i],copyOther,secondCopyBoard);

				int diff = current->getScore() - copyOther ->getScore();
				if (diff > maxScore)
					maxScore = diff;

			}

			if(maxScore < minimax){
				minimax = maxScore;
				bestMove = possiblCurrenteMoves[m];
			}


		}
	}
	return bestMove;
}
