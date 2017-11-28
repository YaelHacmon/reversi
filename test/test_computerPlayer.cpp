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
//NOTICE - google test compares all LOCATIONS by output, so location to comare must be
//less than wanted location by 1
TEST_F(ComputerPlayerTest, AlgorithmChecks) {
  //case 1: test for first move - should be (3,3) or (5,3)
  //our algorithm returns first move found - (3,3) -> (2,2)
  EXPECT_EQ(firstMove, Location(2,2));

  //case 2: test for making the better move when there are other worse possibilities - move should be (2,5) -> (1,4)
  EXPECT_EQ(betterMove, Location(1,4));

  //case 3: test for least worst move, when there are no good choices - should be (3,5) -> (2,4)
  EXPECT_EQ(leastWorstMove, Location(2,4));

  //case 4: test making the winning move - even though there are "better scoring" moves, move should be (1,3) -> (0,2)
  EXPECT_EQ(winMove, Location(0,2));

  //case 5: test making the best move for player, when all moves have no gain for opponent, move should be (3,5) -> (3,5)
  EXPECT_EQ(maxMove, Location(2,4));

  //case 6: test making the best move for player, when all moves have no gain for opponent, move should be (1,4) -> (0,3)
  EXPECT_EQ(tieMove, Location(0,3));
}

