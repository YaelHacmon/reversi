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
			compMove != this->getPossibleMoves().end(); compMove++){

		std::cout << "loop1 for " << *compMove << "\n";
		//copy all participating objects - to work on copies (leave originals untouched)
		Board copyBoard(board);
		Player* copyOther = other->clone();  //using clones for abstract types (no copy c'tor possible)
		Player* copyThis = this->clone();

		/*TODO - vectors are cloned as empty (using size)!!
		 * and yet - loop 2 is entered for the moves (5,6) (6,5) (6,6) in every iteration, because of updateMoveOptions() called
		 * right before loop (moves found are the same - because board has not changed because playGame() did not play).
		 */

		//play move for the current player
		logic-> playMove(*compMove, copyThis, copyBoard, copyOther);

		std::cout << "\tboard after move \n";
		view->printBoard(copyBoard.getBoard(), 8);

		//update the possible moves for the opponent player
		logic-> updateMoveOptions(copyOther, copyBoard);   //TODO - should work
		std::cout << "\tloop1:\n\t\tother possible moves after update: ";
		view->messagePossibleMoves(copyOther->getPossibleMoves());

		//if opponent has no moves - current move will cause a win - make sure it is returned
		if (!copyOther->hasPossibleMoves()) {
			minimax = std::numeric_limits<int>::min();
			bestMove = *compMove;
		}

		//initialize maximal seen score of a player's move to smallest number possible
		int maxScore = numeric_limits<int>::min();

		//for each of the possible moves of the other player - check what is the possible score of move
		/*for(vector<Location>::const_iterator oppMove = copyOther->getPossibleMoves().begin();
				oppMove != copyOther->getPossibleMoves().end(); oppMove++){
			std::cout << "\t\tloop2 for " << *oppMove << "\n";

			//copy all participating objects - to work on copies (leave originals copies as changed in first loop)
			Board secondCopyBoard(copyBoard);
			Player* secondCopyOther = copyOther->clone();
			Player* secondCopyThis = copyThis->clone();


			std::cout << "\tclone#2:\n\t\tother possible moves: ";
			view->messagePossibleMoves(copyOther->getPossibleMoves());
			std::cout << "\n\t\tthis possible moves: ";
			view->messagePossibleMoves(copyThis->getPossibleMoves());
			std::cout<< "\n";

			logic-> updateMoveOptions(secondCopyOther, secondCopyBoard); //TODO - should not have to do this

			//play the possible move for opponent, current player is now the "other player"
			logic-> playMove(*oppMove, secondCopyOther, secondCopyBoard, secondCopyThis);

			//std::cout << "\tboard after SECOND move \n";
			//TODO view->printBoard(secondCopyBoard.getBoard(), 8);

			//get change in scores (opponent's score minus computer's score)
			int diff = secondCopyOther->getScore() - secondCopyThis->getScore();
			//std::cout << "\t\t\tdiff:  " << diff << "\n";


			//if we found a new best move for opponent - save score
			if (diff > maxScore) {
				maxScore = diff;
			}*/


		for(int i=0; i<copyOther->getPossibleMoves().size(); i++){
					std::cout << "\t\tloop2 for " << copyOther->getPossibleMoves()[i] << "\n";

					//copy all participating objects - to work on copies (leave originals copies as changed in first loop)
					Board secondCopyBoard(copyBoard);
					Player* secondCopyOther = copyOther->clone();
					Player* secondCopyThis = copyThis->clone();


					std::cout << "\tclone#2:\n\t\tother possible moves: ";
					view->messagePossibleMoves(copyOther->getPossibleMoves());
					std::cout << "\n\t\tthis possible moves: ";
					view->messagePossibleMoves(copyThis->getPossibleMoves());
					std::cout<< "\n";

					//play the possible move for opponent, current player is now the "other player"
					logic-> playMove(copyOther->getPossibleMoves()[i], secondCopyOther, secondCopyBoard, secondCopyThis);

					//std::cout << "\tboard after SECOND move \n";
					//TODO view->printBoard(secondCopyBoard.getBoard(), 8);

					//get change in scores (opponent's score minus computer's score)
					int diff = secondCopyOther->getScore() - secondCopyThis->getScore();
					//std::cout << "\t\t\tdiff:  " << diff << "\n";


					//if we found a new best move for opponent - save score
					if (diff > maxScore) {
						maxScore = diff;
					}
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
