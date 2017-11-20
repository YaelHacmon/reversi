/*
 * ReversiGame.h
 *
 *  313297897
 *  Author: Yael Hacmon
 */

#ifndef REVERSIGAME_H_
#define REVERSIGAME_H_
#include "Board.h"
#include "Player.h"
#include "ViewGame.h"
#include "GameManger.h"

class ReversiGame : public GameManger
{
public:

	ReversiGame() {}
	virtual ~ReversiGame() {}

	virtual void buildVectorByMoves(vector<Point>& possibleMoves) const;
	virtual void finishSteps(int incScores, int decScores) const;
	virtual void moveInBoard(Point pointToChange);
	virtual void messageWin() const;

	/**
	 * building the vector of possible moves-for each of the empty cells-
	 * check if the point is valid point to the player by check all the eight
	 * directions that are optional.
	 * if the point is valis- insert the vector.
	 *
	 * @param possibleMoves vector of possible moves
	 * @param isValidPoint
	 */
	void fillVectorByPoint(vector<Point>& possibleMoves, Point isValidPoint) const;

	// directions:
	bool checkUp(Point isValidPoint) const;
	bool checkUpRight(Point isValidPoint) const;
	bool checkRight(Point isValidPoint) const;
	bool checkRightDown(Point isValidPoint) const;
	bool checkDown(Point isValidPoint) const;
	bool checkLeftDown(Point isValidPoint) const;
	bool checkLeft(Point isValidPoint) const;
	bool checkUpLeft(Point isValidPoint) const;

};

#endif /* REVERSIGAME_H_ */
