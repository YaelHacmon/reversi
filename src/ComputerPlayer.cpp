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

	// if the opp player have no possible moves, it will return the first possible move.
	//TODO - not sure this is needed, and quite sure it presents a logical problem: consider a situation where other player has no
	//moves, but making a move will create moving options for opponent
	/*if(!other->hasPossibleMoves()){
		return  possiblCurrenteMoves[0];
	}*/

	//execute algorithm
	//for each of the computer player possible move - check what is the highest possible score for opponent
	for(vector<Location>::const_iterator compMove = this->getPossibleMoves().begin();
			compMove != this->getPossibleMoves().end(); ++compMove){

		std::cout << "loop1 for " << *compMove << "\n";
		//copy all participating objects - to work on copies (leave originals untouched)
		Board copyBoard(board);
		Player* copyOther = other->clone();  //using clones for abstract types (no copy c'tor possible)
		Player* copyThis = this->clone();

		/*TODO - vectors are cloned as empty (using size)!!
		 * and yet - loop 2 is entered for the moves (5,6) (6,5) (6,6) in every iteration (which shows something is wrong -
		 * possible moves should be different when playing (3,3) (3,5) (5,3)).
		 * TOTAL: my output for running this (vector size of colens are 0!)
		 * Your possible moves: (3,3),(3,5),(5,3)
			loop1 for (3,3)
					loop2 for (5,6)
					loop2 for (6,5)
					loop2 for (6,6)
			loop1 for (3,5)
					loop2 for (5,6)
					loop2 for (6,5)
					loop2 for (6,6)
			loop1 for (5,3)
					loop2 for (5,6)
					loop2 for (6,5)
					loop2 for (6,6)
		 */

		//play move for the current player
		logic-> playMove(*compMove, copyThis, copyBoard, copyOther);

		//update the possible moves for the opponent player
		logic-> updateMoveOptions(copyOther, copyBoard);

		//initialize maximal seen score of a player's move to smallest number possible
		int maxScore = numeric_limits<int>::min();

		//for each of the possible moves of the other player - check what is the possible score of move
		for(vector<Location>::const_iterator oppMove = copyOther->getPossibleMoves().begin();
				oppMove != copyOther->getPossibleMoves().end(); ++oppMove){
			std::cout << "\tloop2 for " << *oppMove << "\n";

			//copy all participating objects - to work on copies (leave originals copies as changed in first loop)
			Board secondCopyBoard(copyBoard);
			Player* secondCopyOther = copyOther->clone();
			Player* secondCopyThis = copyThis->clone();

			//play the possible move for opponent, current player is now the "other player"
			logic-> playMove(*oppMove, secondCopyOther, secondCopyBoard, secondCopyThis);

			//get change in scores (opponent's score minus computer's score)
			int diff = secondCopyOther->getScore() - secondCopyThis->getScore();

			//if we found a new best move for opponent - save score
			if (diff > maxScore)
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


Player* ComputerPlayer::clone() const
{
	return new ComputerPlayer(*this);
}
