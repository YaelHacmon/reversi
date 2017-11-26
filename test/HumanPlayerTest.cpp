/*
 * HumanPlayerTest.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: roni
 */

#include "HumanPlayerTest.h"

/*
 * Creates players to test cloning, one for each case
 */
HumanPlayerTest::HumanPlayerTest(): hp1("X", Board::BLACK), hp2("O",Board::WHITE), hp3("O",Board::WHITE) {}

/**
 * Sets the test class up - clones the players and changes them according to cases
 */
void HumanPlayerTest::SetUp() {
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

/**
 * Releases the memory
 */
void HumanPlayerTest::TearDown() {
	delete hp1Clone, hp2Clone, hp3Clone;
}



