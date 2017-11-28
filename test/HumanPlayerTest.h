/*
 * HumanPlayerTest.h
 *
 *  Created on: Nov 23, 2017
 *      Author: roni
 */

#ifndef HUMANPLAYERTEST_H_
#define HUMANPLAYERTEST_H_

#include "../gtest_src/gtest/gtest.h"
#include "../include/HumanPlayer.h"

using namespace std;

/**
 * Class to test HumanPlayer. Methods tested:
 * clone() - make sure that on calling method, the possible moves vector is not affected:
 * 			1. clone is exact copy of original
 * 			2. acting on clone does not change original
 * 			3. acting on original does not change clone
 */
class HumanPlayerTest: public testing::Test {
public:
  //Default c'tor.
  HumanPlayerTest() :
      hp1("X", Board::BLACK), hp2("O", Board::WHITE), hp3("O", Board::WHITE), hp1Clone(
          NULL), hp2Clone(NULL), hp3Clone(NULL) {
  }

  //sets up the tests
  virtual void SetUp();

  //releases the memory used
  virtual void TearDown();

protected:
  HumanPlayer hp1, hp2, hp3;
  Player *hp1Clone, *hp2Clone, *hp3Clone;
};

#endif /* HUMANPLAYERTEST_H_ */
