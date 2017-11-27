/*
 * Roni Fultheim, ID: 313465965
 * Yael Hacmon, ID: 313297897
 * ComputerPlayer.cpp
 */
#include <iostream>
#include <limits>
#include "../include/MoveLogic.h"
#include "../include/ComputerPlayer.h"
#include <vector>

using namespace std;

//according to minimax algorithm
Location ComputerPlayer::getNextMove(const ViewGame* view, const MoveLogic* logic, const Board& board, const Player* other)
{
	//initialize minimax value to maximum value possible
	int minimax = std::numeric_limits<int>::max();

	//initialize best move to fist possible move - will make sure move returned is legal at any case
	Location bestMove(this->getPossibleMoves()[0]);

	//execute algorithm
	//for each of the computer player possible move - check what is the highest possible score for opponent
	for(vector<Location>::const_iterator compMove = this->getPossibleMoves().begin();
			compMove != this->getPossibleMoves().end(); compMove++) {

		//copy all participating objects - to work on copies (leave originals untouched)
		Board copyBoard(board);
		Player* copyOther = other->clone();  //using clones for abstract types (no copy c'tor possible)
		Player* copyThis = this->clone();


		//play move for the current player
		logic-> playMove(*compMove, copyThis, copyBoard, copyOther);

		//update the possible moves for the opponent player
		logic-> updateMoveOptions(copyOther, copyBoard);


		//if opponent has no moves - current move will cause a win - make sure it is returned
		if (!copyOther->hasPossibleMoves()) {
			minimax = std::numeric_limits<int>::min();
			bestMove = *compMove;
		}


		//initialize maximal seen score of a player's move to smallest number possible
		int maxScore = numeric_limits<int>::min();

		//for each of the possible moves of the other player - check what is the possible score of move
		for(vector<Location>::const_iterator oppMove = copyOther->getPossibleMoves().begin();
				oppMove != copyOther->getPossibleMoves().end(); oppMove++){

			//copy all participating objects - to work on copies (leave originals copies as changed in first loop)
			Board secondCopyBoard(copyBoard);
			Player* secondCopyOther = copyOther->clone();
			Player* secondCopyThis = copyThis->clone();

			//play the possible move for opponent, current player is now the "other player"
			logic-> playMove(*oppMove, secondCopyOther, secondCopyBoard, secondCopyThis);

			//get change in scores (opponent's score minus computer's score)
			int diff = secondCopyOther->getScore() - secondCopyThis->getScore();

			//if we found a new best move for opponent - save score
			if (diff > maxScore) {
				maxScore = diff;
			}

			//if best move opponent can play is worse then found best move for opponent -
			//current move is our best choice - save it
			if(maxScore < minimax){
				minimax = maxScore;
				bestMove = *compMove;
			}
		}

		//return best move
		return bestMove;
	}
}

Player* ComputerPlayer::clone() const
{
	return new ComputerPlayer(*this);
}
