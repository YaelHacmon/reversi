/*
 * GameManager.h
 */

#ifndef GameManager_H_
#define GameManager_H_

#include <iostream>
#include "Board.h"
#include "MoveLogic.h"
#include "Player.h"
#include "Location.h"
#include "ViewByConsole.h"
#include "HumanPlayer.h"

/**
 * Controls the game flow of a Reversi game when given a board, two players
 * and an object to control the logic of every move.
 *
 * Is responsible for playing the turns, knowing and notifying when the game ends, and printing
 * messages to the players.
 */
class GameManager {
public:
	/**
	 * Constructor taking a board on which to play game, two players, and the logic of the moves.
	 * @param b board of game
	 * @param black black player
	 * @param white white player
	 * @param log logic to handle moves
	 */
	GameManager(ViewGame* view, Board& b, Player* black, Player* white, MoveLogic* log);

	/**
	 * Virtual destructor.
	 */
	virtual ~GameManager();

	/**
	 * Plays game with the given board, players and logic.
	 */
	virtual void playGame() = 0;

private:
	//board of game
	Board board_;

	//current player - by reference, to allow polymorphism. Starting player is black by default.
	Player* currPlayer_;

	//white player - by reference, to allow polymorphism. Opposite player is black by default.
	Player* oppPlayer_;

	//handles logic of moves - by reference, to allow polymorphism
	MoveLogic* logic_;

	//way to view game
	ViewGame* view_;

	/**
	 * Returns winner of game.
	 * @return player who won this game
	 */
	virtual void showWinner();
};


#endif /* GameManager_H_ */
