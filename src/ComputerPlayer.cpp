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
Location ComputerPlayer::getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other)
{

	int minimax = numeric_limits<int>::infinity();

	int maxScore = 0;

	Location bestMove(-1,-1);

	vector<Location> possiblCurrenteMoves = this->getPossibleMoves();
	vector<Location> possiblOtherMoves = other->getPossibleMoves();

	// if the opp player have no possible moves, it will return the first possible move.
	if(possiblOtherMoves.size() == 0){
		return  possiblCurrenteMoves[0];
	}

	//otherwise - execute algorithm
	//for each of the computer player possible move - check what is the highest possible score for opponent
	for(int m =0; m < possiblCurrenteMoves.size; ++m){

		//copy all participating objects - to work on copies (leave originals untouched)
		Board copyBoard(board);
		Player* copyOther = other->clone();
		Player* copyThis = this->clone();

		//play move for the current player
		logic-> playMove(possiblCurrenteMoves[m],this,copyBoard,copyOther);

		//update the possible moves for the opponent player
		logic-> updateMoveOptions(copyOther,copyBoard);

		//for each of the possible moves of the other player - check what is the possible score of move
		for(int i = 0; i < possiblOtherMoves.size; ++i){

			//copy all participating objects - to work on copies (leave originals copies as changed in first loop)
			Board secondCopyBoard(board);
			Player* secondCopyOther = copyOther->clone();
			Player* secondCopyThis = copyThis->clone();

			//play the possible move for opponent, current player is now the "other player"
			logic-> playMove(possiblOtherMoves[i],secondCopyOther,secondCopyBoard, secondCopyThis);

			//get change in scores
			int diff = secondCopyThis->getScore() - secondCopyOther->getScore();

			//if we found a new best move for opponent - save score
			if (diff > maxScore)
				maxScore = diff;

		}

		//if best move opponent can play is worse then found best move for opponent -
		//current move is our best choice - save it
		if(maxScore < minimax){
			minimax = maxScore;
			bestMove = possiblCurrenteMoves[m];
		}
	}

	//return best move
	return bestMove;
}
