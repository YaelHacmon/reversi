/*
 * Roni Fultheim, ID: 313465965
 * StandardMoveLogic.cpp
 */

#include  "StandardMoveLogic.h"
#include <stdlib> //for abs
#include <vector>


void StandardMoveLogic::playMove(const Location& move, Player* player, Board& board, Player* opponent) const {
	//if move is illegal - do nothing
	if (!isMoveAllowed(move, player)) {
		return;
	}

	//initialize an array of 8 locations with the given move
	Location dirs[8] = {move, move, move, move, move, move, move, move};

	//get location of last square to flip in move in all directions
	possibleMoveDirections(dirs, player->getColor(), board);


	//in case move is at edge of board
	if (board.isEdge(move)) {
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


	//go over directions and change colors in board + update players' scores
	for (int i = 0; i<8; i++) {
		//get jumps from move to end of range
		int rowJumps = jumps(move.row(), dirs[i].row());
		int colJumps = jumps(move.column(), dirs[i].column());

		//change color
		board.flipColorInRange(move, dirs[i], rowJumps, colJumps);

		//update scores
		//if the change has been in rows - use rows to update the scores
		if (rowJumps != 0) {
			//calculate difference (absolute value of move's row minus end of range's row)
			int diff = abs(move.row()-dirs[i].row());
			//increase difference from opponent and add to playing player
			player->increaseScore(diff);
			opponent->decreaseScore(diff);

		//otherwise, if the change has been in columns - use columns to update the scores
		} else if (colJumps != 0) {
			//calculate difference (absolute value of move's row minus end of range's row)
			int diff = abs(move.column()-dirs[i].column());
			//increase difference from opponent and add to playing player
			player->increaseScore(diff);
			opponent->decreaseScore(diff);
		}
		//otherwise - there has been no change in the scores in this direction - do nothing
	}

	//make original move
	board.makeInColor(player->getColor(), move);
	//add 1 to player's score
	player->increaseScore(1);
}


bool StandardMoveLogic::isPossibleMoveByLogic(const Player::ColorOfPlayer color, const Location& location, const Board& board) const {
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


void StandardMoveLogic::possibleMoveDirections(Location* dirs, const Player::ColorOfPlayer pColor, const Board& board) const {
	/* IDEA:
	 * Checks all directions of possible consecutive opposite colored sequence of squares relative to the given location,
	 * and saves location of last square in opposite-colored range.
	 * A direction which is an option for a move must have:
	 * 1. at least one neighboring square with the opposite color
	 * 2. the consecutive sequence of opposite colored neighboring squares ends with a same-colored square. */

	//get size of board indexed to c++ indexing
	int size = board.size()-1;

	//initialize an array of 8 locations with the wanted directions of ranges - diagonally  ("towards board corners" - method
	//knows to do that even when the move is not located in the center) and straight (to board edges)
	Location ranges[8] = {Location(0,0), Location(0, dirs[0].column()), Location (0, size), Location (dirs[0].row(), size),
			Location (size, size), Location (size, dirs[0].column()), Location (size, 0), Location (dirs[0].row(), 0)};

	//save move
	Location move = dirs[0];

	//for each direction range in ranges
	for (int i = 0; i<8; i++) {
		//if move is not this edge of board - get last color in that direction
		if (move != ranges[i]) {
			//get last square in range with the opposite color than move's
			Location loc(lastInColorRange(pColor, move, ranges[i], board));
			dirs[i] = lastInColorRange(pColor, move, ranges[i], board);
		}
	}
}
