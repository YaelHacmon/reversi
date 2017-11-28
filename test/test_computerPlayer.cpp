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
  //case 1: test for first move - should be (2,2) or (4,2)
  //our algorithm returns first move found - (2,2)
  EXPECT_EQ(firstMove, Location(2,2));

  //case 2: test for making the better move when there are other worse possibilities - move should be (1,5)
  EXPECT_EQ(betterMove, Location(1,5));

  //case 3: test for a series of moves - should be (2,0)
  EXPECT_EQ(moveSeriesMove, Location(2,0));

  //case 4: test making the winning move - even though there are "better scoring" moves, move should be (0,4)
  EXPECT_EQ(winMove, Location(0,4));

  //case 5: test making the best move for player, when all moves have no gain for opponent, move should be (3,7)
  EXPECT_EQ(maxMove, Location(3,7));

  //case 6: test making the best move for player, when all moves have no gain for opponent, move should be (0,3)
  EXPECT_EQ(tieMove, Location(0,3));
}

