/*
 * Roni Fultheim, ID: 313465965
 * StandardMoveLogic.cpp
 */

#include  "StandardMoveLogic.h"
#include <vector>


void StandardMoveLogic::playMove(const Location& move, const Player* player, Board* board) const {
	//if move is illegal - do nothing
	if (!isMoveAllowed(move, player, board)) {
		return;
	}

	//initialize an array of 8 locations with the given move
	Location dirs[8] = {move, move, move, move, move, move, move, move};

	//get location of last square to flip in move in all directions
	possibleMoveDirections(dirs, player->getColor(), board);


	//in case move is at edge of board
	if (board->isEdge(move)) {
		//making sure a direction does not appear twice - to avoid flipping twice at edge case
		//when move=edge, there are two overlapping directions (corner and edge withrow/column of move), so flipping is done twice
		for (int i=0; i<8; i++) {
			for (int j=i+1; j<8; j++) {
				//if the location of a last square in one direction is equal to that of another (as in edge case - overlapping directions)
				if (dirs[i]==dirs[j]) {
					//change earlier direction to out of board (to allow further comparison) to out of range location
					dirs[i] = move;
				}
			}
		}
	}


	//go over directions and change colors in board
	for (int i = 0; i<8; i++) {
		//get jumps from move to end of range
		int rowJumps = jumps(move.row(), dirs[i].row());
		int colJumps = jumps(move.column(), dirs[i].column());

		//change color
		board->flipColorInRange(move, dirs[i], rowJumps, colJumps);
	}

	//make original move
	board->makeInColor(player->getColor(), move);
}


bool StandardMoveLogic::isMoveAllowed(const Location& move, const Player* player, const Board* board) const {
	/*RULES: a move is allowed if:
	1. location is in range of board
	2. location is empty
	3. location can be an option for a move (code shared by this function) */

	//check that location is in board range, if not - return false
	if (!board->isInBoardRange(move)) {
		return false;
	}

	//check that square is empty before checking for possible directions for move - if not - return false
	if (!board->isCellEmpty(move)) {
		return false;
	}

	//check if this is an option for a move:
	//initialize an array of 8 locations with the given move
	Location dirs[8] = {move, move, move, move, move, move, move, move};

	//get locations of last squares to flip in move in all directions
	possibleMoveDirections(dirs, player->getColor(), board);

	//if at least one direction is not the original move - there is a possible switch of colors
	for (int i = 0; i<8; i++) {
		if (dirs[i] != move) {
			return true;
		}
	}

	//otherwise all in all directions move is the last square before matching square color - no way to move
	return false;
}


bool StandardMoveLogic::isPossibleMoveByLogic(Player::ColorOfPlayer color, Location& location, const Board* board) const {
	//initialize an array of 8 locations with the given move
	Location dirs[8] = {location, location, location, location, location, location, location, location};

	//get location of last square to flip in move in all directions
	possibleMoveDirections(dirs, color, board);

	//check that at least one direction is different than original move
	for (int i = 0; i<8; i++) {
		if (dirs[i] != location) {
			return true;
		}
	}
	//otherwise - no directions to move to
	return false;
}


void StandardMoveLogic::possibleMoveDirections(Location* dirs, const Player::ColorOfPlayer pColor, const Board* board) const {
	/* IDEA:
	 * Checks all directions of possible consecutive opposite colored sequence of squares relative to the given location,
	 * and saves location of last square in opposite-colored range.
	 * A direction which is an option for a move must have:
	 * 1. at least one neighboring square with the opposite color
	 * 2. the consecutive sequence of opposite colored neighboring squares ends with a same-colored square. */

	//get size of board indexed to c++ indexing
	int size = board->size()-1;

	//initialize an array of 8 locations with the wanted directions of ranges - diagonally  ("towards board corners" - method
	//knows to do that even when the move is not located in the center) and straight (to board edges)
	Location ranges[8] = {Location(0,0), Location(0, dirs[0].column()), Location (0, size), Location (dirs[0].row(), size),
			Location (size, size), Location (size, dirs[0].column()), Location (size, 0), Location (dirs[0].row(), 0)};

	//save original move - in case all dirctions change
	Location move = dirs[0];

	//for each direction range in ranges
	for (int i = 0; i<8; i++) {
		//if move is not this edge of board - get last color in that direction
		if (move != ranges[i]) {
			//get last square in range with the opposite color than move's
			dirs[i] = lastInColorRange(pColor, move, ranges[i], board);
		}
	}
}
