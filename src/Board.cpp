/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#include <cstdlib>
#include <stdexcept>
#include "Board.h"

using namespace std;


Board::Board(int size): size_(size) {
	//allocate array of pointers of squares to represent board's first column (size_= #of rows)
	// wrapped in try-catch block as expected
	try {
		gameBoard_ = new ElementInBoard*[size_];
	} catch (...) {
		cout << "Allocation of board failed: EXITING GAME" << endl;
		exit(0);
	}

	//allocate all rows (size_= #of columns), and initialize matrix with empty squares
	for (int i = 0 ; i<size_; i++) {
		// allocate rows
		// wrapped in try-catch block as expected
		try {
			gameBoard_[i] = new ElementInBoard[size_];
		} catch (...) {
			cout << "Allocation of board failed: EXITING GAME" << endl;
			exit(0);
		}

		// initialize empty squares
		for (int j = 0 ; j< size_; j++) {
			//a cell will be empty by default
			gameBoard_[i][j] = EMPTY;
			//adding cell to list of empty cells
			emptyCells_.push_back(Location(i, j));
		}
	}

	//initialize board for the game - white is always at upper left corner of initialization square
	//notice that c++ indexing requires to divide size in 2 then subtract 1 to reach the center of board
	//initialize white squares
	makeInColor(WHITE, Location(size_/2-1, size_/2-1));
	makeInColor(WHITE, Location(size_/2, size_/2));
	//initialize black squares
	makeInColor(BLACK, Location(size_/2-1, size_/2));
	makeInColor(BLACK, Location(size_/2, size_/2-1));
}


Board::~Board() {
	//delete rows of matrix
	for (int i = 0; i<size_; i++) {
		delete gameBoard_[i];
	}
	//delete first column
	delete gameBoard_;
}

Board::Board(Board& other): size_(other.size())
{
	try {
		gameBoard_ = new ElementInBoard*[size_];
	} catch (...) {
		cout << "Allocation of board failed: EXITING GAME" << endl;
		exit(0);
	}

	for (int i = 0 ; i<size_; i++) {

		// allocate rows
		// wrapped in try-catch block as expected
		try {
			gameBoard_[i] = new ElementInBoard[size_];
		} catch (...) {
			cout << "Allocation of board failed: EXITING GAME" << endl;
			exit(0);
		}

		// copy the other Board's cell value in the new board
		for (int j = 0 ; j< size_; j++) {
			gameBoard_[i][j] = other.gameBoard_[i][j];
			emptyCells_ = other.emptyCells_;

		}
	}
}

Board::ElementInBoard**Board::getBoard()const
{
	return gameBoard_;
}


int Board::size() const {
	return size_;
}


bool Board::isCellWhite(const Location& loc) const {
	return getCell(loc)==WHITE;
}


bool Board::isCellBlack(const Location& loc) const {
	return getCell(loc)==BLACK;
}


bool Board::isCellEmpty(const Location& loc) const {
	return getCell(loc)==EMPTY;
}


bool Board::compareCellColors(const Location& loc1, const Location& loc2) const {
	return getCell(loc1)==getCell(loc2);
}

bool Board::compareCellColors(const ElementInBoard& c, const Location& loc) const {
	return getCell(loc)==c;
}

void Board::makeInColor(const ElementInBoard& c, const Location& loc) {
	//if square is not empty - throw exception (cannot make a non-empty square in a color)
	if (!isCellEmpty(loc)) {
		throw logic_error("Logic problem: tried switching an empty square's color\n");
	}

	//else - change color of cell
	gameBoard_[loc.row()][loc.column()] = c;
	//remove from list of empty cells
	emptyCells_.remove(loc);
	//TODO  - could not use:
	//removeCellFromEmptyList(loc);
}


void Board::flipColorInRange(const Location& prevStart, const Location& end, int rowJumps, int colJumps) {
	//make sure both prevStart and end are in range of board
	if (!isInBoardRange(prevStart) || !isInBoardRange(end)) {
		return;
	}

	//avoid infinite loop in case of no jumps
	if (rowJumps == 0 && colJumps == 0) {
		return;
	}

	//iterate over board and change the location:
	//initialize start of range
	Location curr(prevStart);

	//if end location cannot be reached by given jumps - there is no way to know when to stop
	//check if row/column jumps are 0 before using the % operation (undefined for 0)
	if (((rowJumps != 0) && ((end.row()-curr.row()) % rowJumps != 0)) ||
			((colJumps) != 0 &&  ((end.column()-curr.column()) % colJumps != 0))) {
		//return to avoid infinite loop
		return;
	}

	//while location is still in given range - has not yet reached end
	while (curr != end) {
		//first move to next square (started with square previous to start)
		curr.increment(rowJumps, colJumps);
		//then flip next square
		ElementInBoard e = getCell(curr);
		if (e==WHITE) {
			gameBoard_[curr.row()][curr.column()] = BLACK;
		} else if (e==BLACK) {
			gameBoard_[curr.row()][curr.column()] = WHITE;
		} else {
			throw logic_error("tried to flip an emty cell");
		}
	}
}


bool Board::isInBoardRange(const Location& loc) const {
	//check that row and column values are between 0 and board size-1
	return (loc.row() >= 0 && loc.column() >= 0 && loc.row() < size_ && loc.column() < size_);
}


bool Board::isEdge(const Location& loc) const {
	return (loc.row()==0 || loc.row()==(size_-1) || loc.column()==0 || loc.column()==(size_-1));
}


bool Board::isBoardFull() const {
	//if list is empty - board is full
	return emptyCells_.empty();
}


std::list<Location>::const_iterator Board::emptyCellsBegin() const {
	return emptyCells_.begin();
}


std::list<Location>::const_iterator Board::emptyCellsEnd() const {
	return emptyCells_.end();
}


const Board::ElementInBoard& Board::getCell(const Location& loc) const {
	return gameBoard_[loc.row()][loc.column()];
}


void Board::removeCellFromEmptyList(Location& removalPoint) {
	emptyCells_.remove(removalPoint);
}
