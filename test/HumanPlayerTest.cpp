/*
 * HumanPlayerTest.cpp
 *
 *  Created on: Nov 27, 2017
 *      Author: roni
 */

#include "HumanPlayerTest.h"

HumanPlayerTest::HumanPlayerTest(): hp1("X", Board::BLACK), hp2("O",Board::WHITE), hp3("O",Board::WHITE) {}


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

void HumanPlayerTest::TearDown() {
	delete hp1Clone, hp2Clone, hp3Clone;
}

