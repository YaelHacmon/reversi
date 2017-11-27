/*
 * test_computerPlayer.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: roni
 */

#include "../gtest_src/gtest/gtest.h"
#include "ComputerPlayerTest.h"

//tests cloning
TEST_F(ComputerPlayerTest, CloningChecks) {
	//test for cloning correctly
	EXPECT_EQ(hp3.getPossibleMoves(), hp3Clone->getPossibleMoves());
	//test for no changes in clone when changing original
	EXPECT_NE(hp1.getPossibleMoves(), hp1Clone->getPossibleMoves());
	//test for no changes in original when changing clone
	EXPECT_NE(hp2.getPossibleMoves(), hp2Clone->getPossibleMoves());
}

//tests getNextMove minimax algorithm
TEST_F(ComputerPlayerTest, AlgorithmChecks) {
	//case 1: test for first move - should be (3,3) or (5,3)
	EXPECT_TRUE((firstMove==Location(3,3)) || (firstMove==Location(5,3)));

	//case 2: test for making the better move when there are other worse possibilities - should be either (1,5), (5,3), or (5,5)
	EXPECT_TRUE((betterMove==Location(1,5)) || (betterMove==Location(5,3)) || (betterMove==Location(5,5)));

	//case 3: test for least worst move, when there are no good choices - should be (4,7) or (7,4)
	EXPECT_TRUE((leastWorstMove==Location(4,7)) || (leastWorstMove==Location(7,4)));

	//case 4: test making the winning move - even though there are "better scoring" moves, move should be (0,4)
	EXPECT_EQ(winMove, Location(0,4));

	//case 5: test making the best move for player, when all moves have no gain for opponent
	EXPECT_EQ(maxMove, Location(6,3));

	//case 6: test making the best move for player, when all moves have no gain for opponent
	EXPECT_EQ(tieMove, Location(0,3));
}



