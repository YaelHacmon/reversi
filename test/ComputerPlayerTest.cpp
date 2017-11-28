/*
 * ComputerPlayerTest.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: roni
 */

#include "ComputerPlayerTest.h"

/*
 * Default c'tor, creates players for testing the cloning and the getNextMove, and initializes all boards at size 8 besides
 * for tieBoard - at size 4 (for easier testing). All moves' locations are initialized at (-1,-1)
 */
ComputerPlayerTest::ComputerPlayerTest() :
    hp1("X", Board::BLACK), hp2("O", Board::WHITE), hp3("O", Board::WHITE), hp1Clone(
        NULL), hp2Clone(NULL), hp3Clone(NULL), player("O", Board::WHITE), opponent(
        "X", Board::BLACK), tieBoard(4), firstMove(-1, -1), betterMove(-1, -1), leastWorstMove(
        -1, -1), winMove(-1, -1), tieMove(-1, -1), maxMove(-1, -1) {
}

void ComputerPlayerTest::SetUp() {
  //CLONE
  //add location to each player
  vector < Location > locs;
  locs.push_back(Location(2, 3));
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

  //GET NEXT MOVE - setup
  setFirstBoard();
  setBetterBoard();
  setLeastWorstBoard();
  setWinBoard();
  setMaxBoard();
  setTieBoard();
}

void ComputerPlayerTest::TearDown() {
  delete hp1Clone, hp2Clone, hp3Clone;
}

//sets for check of first move of AI in game, given opponent played (3,4)
void ComputerPlayerTest::setFirstBoard() {
  //clear player's scores to be 2 and 2
  clearScores();

  //play move
  vector < Location > locs;
  locs.push_back(Location(2, 3));
  playVector(locs, firstBoard);

  //get move - should be (3,3) or (5,3) - by our example
  mvl.updateMoveOptions(&player, firstBoard);
  firstMove = player.getNextMove(&v, &mvl, firstBoard, &opponent);
}

//sets for check of playing a better move: a line of blacks, ending with a white then a black.
//making the move at the other end of that row will only allow for the black player to flip the whole line back.
//player should choose some other move [(1,5) (5,3) (5,5)]
void ComputerPlayerTest::setBetterBoard() {
  //clear player's scores to be 2 and 2
  clearScores();

  //create line - play (5,4) to flip (4,4)
  vector < Location > locs;
  locs.push_back(Location(5, 4));
  playVector(locs, betterBoard);

  //create line of blacks with white then black at end - make (2,4) and (7,4) black
  locs.clear();
  locs.push_back(Location(2, 4));
  locs.push_back(Location(7, 4));
  setBlackMoves(locs, betterBoard, opponent);
  //set white at (6,4)
  locs.clear();
  locs.push_back(Location(6, 4));
  setWhiteMoves(locs, betterBoard, player);

  //get computer's move - should be either (1,5), (5,3), or (5,5)
  mvl.updateMoveOptions(&player, betterBoard);
  betterMove = player.getNextMove(&v, &mvl, betterBoard, &opponent);
}

//set board so that there is no good moves, but two moves that less bad than other possible moves
void ComputerPlayerTest::setLeastWorstBoard() {
  //clear player's scores to be 2 and 2
  clearScores();

  //make black locations, so that black will have better score at any wite move
  vector < Location > locs;
  //make black all surrounding locations, so that black will have no possible moves
  locs.push_back(Location(4, 5));
  locs.push_back(Location(4, 6));
  locs.push_back(Location(5, 4));
  locs.push_back(Location(6, 4));
  setBlackMoves(locs, leastWorstBoard, opponent);

  //get computer's move - should be (4,7) or (7,4) - symmetric
  mvl.updateMoveOptions(&player, leastWorstBoard);
  leastWorstMove = player.getNextMove(&v, &mvl, leastWorstBoard, &opponent);
}

//set board so that there is one winning move and other possible moves that are better scoring
//black will have no moves when (0,4) will be played, and will continue playing for any other moves
void ComputerPlayerTest::setWinBoard() {
  //clear player's scores to be 2 and 2
  clearScores();

  //play (2,3)
  vector < Location > locs;
  locs.push_back(Location(2, 3));
  locs.push_back(Location(2, 4));
  playVector(locs, winBoard);

  //make black all surrounding locations, so that black will have no possible moves
  locs.clear();
  locs.push_back(Location(0, 3));
  locs.push_back(Location(1, 3));
  locs.push_back(Location(1, 4));
  for (int i = 0; i <= 5; i++) {
    locs.push_back(Location(i, 5));
  }
  locs.push_back(Location(5, 3));
  locs.push_back(Location(4, 2));
  setBlackMoves(locs, winBoard, opponent);

  //get computer's move - should be (0,4) and NOT (5,1) which is "better scoring" by 1, but will allow game to continue
  mvl.updateMoveOptions(&player, winBoard);
  winMove = player.getNextMove(&v, &mvl, winBoard, &opponent);
}

//sets board where all moves are of non-positive score - player should choose the smallest (no gain for opponent at any case)
void ComputerPlayerTest::setMaxBoard() {
  //clear player's scores to be 2 and 2
  clearScores();

  //add white moves
  vector < Location > locs;
  locs.push_back(Location(5, 4));
  locs.push_back(Location(6, 4));
  locs.push_back(Location(7, 4));
  setWhiteMoves(locs, maxBoard, player);
  //add black move
  locs.clear();
  locs.push_back(Location(5, 3));
  setBlackMoves(locs, maxBoard, opponent);

  //get computer's move - should be (6,3), which has the lowest score
  mvl.updateMoveOptions(&player, maxBoard);
  maxMove = player.getNextMove(&v, &mvl, maxBoard, &opponent);
}

//sets the 4*4 board (done for easier testing, initialized at constructor) for a case when
//one move results in a tie, and the other move results in the opponent winning
void ComputerPlayerTest::setTieBoard() {
  //clear player's scores to be 2 and 2
  clearScores();

  //use playing moves to create wanted arrangement
  //play white first move at (2,0)
  mvl.updateMoveOptions(&player, tieBoard);
  mvl.playMove(Location(2, 0), &player, tieBoard, &opponent);
  //play black move at (3,2)
  mvl.updateMoveOptions(&opponent, tieBoard);
  mvl.playMove(Location(3, 2), &opponent, tieBoard, &player);

  //set rest of white moves
  vector < Location > locs;
  locs.push_back(Location(0, 1));
  locs.push_back(Location(0, 2));
  locs.push_back(Location(1, 0));
  locs.push_back(Location(2, 3));
  setWhiteMoves(locs, tieBoard, player);
  //set rest of black moves
  locs.clear();
  locs.push_back(Location(0, 0));
  locs.push_back(Location(3, 0));
  locs.push_back(Location(3, 1));
  locs.push_back(Location(3, 3));
  setBlackMoves(locs, tieBoard, opponent);

  //get computer's move - should be (0,3) to result in a tie and NOT (5,1) which results in opponent winning
  mvl.updateMoveOptions(&player, tieBoard);
  tieMove = player.getNextMove(&v, &mvl, tieBoard, &opponent);
}

//Plays a given vector of moves on the given board, black (opponent) first
void ComputerPlayerTest::playVector(vector<Location>& locs, Board& b) {
  for (vector<Location>::const_iterator it = locs.begin(); it != locs.end();
      it++) {
    //play opponent's move
    mvl.updateMoveOptions(&opponent, b);
    mvl.playMove(*it, &opponent, b, &player);
    //if player must make a move (in case of even number of moves) - make it
    if (it != locs.end()) {
      mvl.updateMoveOptions(&player, b);
      mvl.playMove(*it, &player, b, &opponent);
    }
  }
}

//sets white moves by given locations
//accepts the player in case that in the future we would want the opponent white and the computer black
void ComputerPlayerTest::setWhiteMoves(vector<Location>& locs, Board& b,
    Player& p) {
  for (vector<Location>::const_iterator it = locs.begin(); it != locs.end();
      it++) {
    b.makeInColor(Board::WHITE, *it);
    p.increaseScore(1);
  }
}

//sets white moves by given locations
//accepts the player in case that in the future we would want the opponent white and the computer black
void ComputerPlayerTest::setBlackMoves(vector<Location>& locs, Board& b,
    Player& p) {
  for (vector<Location>::const_iterator it = locs.begin(); it != locs.end();
      it++) {
    b.makeInColor(Board::BLACK, *it);
    p.increaseScore(1);
  }
}

//sets scores back to 2 and 2, to allow for new game playing
void ComputerPlayerTest::clearScores() {
  player.decreaseScore(player.getScore());
  opponent.decreaseScore(opponent.getScore());
  player.increaseScore(2);
  opponent.increaseScore(2);
}

