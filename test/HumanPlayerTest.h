/*
 * HumanPlayerTest.h
 *
 *  Created on: Nov 23, 2017
 *      Author: roni
 */

#ifndef HUMANPLAYERTEST_H_
#define HUMANPLAYERTEST_H_

#include "../gtest_src/gtest/gtest.h"
#include "HumanPlayer.h"

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
		/**
		 * Default c'tor.
		 */
		HumanPlayerTest(): hp1("X", Board::BLACK), hp2("O",Board::WHITE) {}


		virtual void SetUp() {
			//add location to each player
			vector<Location> locs;
			locs.push_back(Location(2,3));
			hp1.updatePossibleMoves(locs);
			hp2.updatePossibleMoves(locs);
			locs.push_back(Location(5, 6));
			hp3.updatePossibleMoves(locs);
			//clone
			hp1Clone = hp1.clone();
			hp2Clone = hp2.clone();
			hp3Clone = hp3.clone();

			locs.push_back(Location(4, 5));
			//make change to original
			hp1.updatePossibleMoves(locs);
			//make change to clone
			hp2Clone->updatePossibleMoves(locs);
		}

		virtual void TearDown() {
			delete hp1Clone, hp2Clone, hp3Clone;
		}

	protected:
		HumanPlayer hp1, hp2, hp3;
		Player *hp1Clone, *hp2Clone, *hp3Clone;
};



#endif /* HUMANPLAYERTEST_H_ */
