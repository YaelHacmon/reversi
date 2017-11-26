/*
 * ComputerPLayerTest.h
 *
 *  Created on: Nov 23, 2017
 *      Author: roni
 */

#ifndef COMPUTERPLAYERTEST_H_
#define COMPUTERPLAYERTEST_H_
#include "../gtest_src/gtest/gtest.h"
#include "ComputerPlayer.h"

/**
 * Class to test ComputerPlayer. Should test:
 *
 * A. clone() - make sure that on calling method, the possible moves vector is not affected:
 * 			1. clone is exact copy of original
 * 			2. acting on clone does not change original
 * 			3. acting on original does not change clone
 *
 * 	B. getNextMove() - make sure that player really does return the optimal move for him. Cases
 * 			1. player return (3,3) or (5,3) after opponent's playing (3,4) - like example given (First)
 * 			2. player returns minimax move (better move) if there is a good and bad option (Better)
 * 			3. player returns least worst move for him, when all moves have gain for opponent (LeastWorst)
 * 			4. player returns minimax move also when it causes the opponent to have no moves (aka player wins) (Win)
 * 			5. player returns the best option for him, when opponent has no gain from any move (Max)
 * 			6. player returns tie move if there is no winning move (Tie)
 */
class ComputerPlayerTest: public testing::Test {
	public:
		//Default c'tor.
		ComputerPlayerTest();

		//sets up the tests
		virtual void SetUp();

		//releases the memory allocated
		virtual void TearDown();

	protected:
		//for clone()
		ComputerPlayer hp1, hp2, hp3, *hp1Clone, *hp2Clone, *hp3Clone;
		//for getNextMove()
		ViewByConsole v;
		StandardMoveLogic mvl;
		ComputerPlayer player, opponent;
		Board firstBoard, betterBoard, leastWorstBoard, winBoard, tieBoard, maxBoard;
		Location firstMove, betterMove, leastWorstMove, winMove, tieMove, maxMove;


		//sets for check of first move of AI in game, given opponent played (3,4)
		void setFirstBoard();

		//sets for check of playing a better move: a line of blacks, ending with a white then a black.
		//making the move at the other end of that row will only allow for the black player to flip the whole line back.
		//player should choose some other move [(1,5) (5,3) (5,5)]
		void setBetterBoard();

		//set board so that there is no good moves, but two moves that less bad than other possible moves
		void setLeastWorstBoard();

		//set board so that there is one winning move and other possible moves that are better scoring
		//black will have no moves when (0,4) will be played, and will continue playing for any other moves
		void setWinBoard();

		//sets board where all moves are of non-positive score - player should choose the smallest (no gain for opponent at any case)
		void setMaxBoard();

		//sets the 4*4 board (done for easier testing, initialized at constructor) for a case when
		//one move results in a tie, and the other move results in the opponent winning
		void setTieBoard();

		//Plays a given vector of moves on the given board, black (opponent) first
		void playVector(vector<Location>& locs, Board& b);

		//sets white moves by given locations
		//accepts the player in case that in the future we would want the opponent white and the computer black
		void setWhiteMoves(vector<Location>& locs, Board& b, Player& p);

		//sets white moves by given locations
		//accepts the player in case that in the future we would want the opponent white and the computer black
		void setBlackMoves(vector<Location>& locs, Board& b, Player& p);

		//sets scores back to 2 and 2, to allow for new game playing
		void clearScores();
};


#endif /* COMPUTERPLAYERTEST_H_ */
