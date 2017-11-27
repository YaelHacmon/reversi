/*
 * test_humanPlayer.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: roni
 */

#include "../gtest_src/gtest/gtest.h"
#include "HumanPlayerTest.h"

TEST_F(HumanPlayerTest, CloningChecks) {
	//test for cloning correctly
	EXPECT_EQ(hp3.getPossibleMoves(), hp3Clone->getPossibleMoves());
	//test for no changes in clone when changing original
	EXPECT_NE(hp1.getPossibleMoves(), hp1Clone->getPossibleMoves());
	//test for no changes in original when changing clone
	EXPECT_NE(hp2.getPossibleMoves(), hp2Clone->getPossibleMoves());
}


