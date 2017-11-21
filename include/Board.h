/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Location.h"
#include <list>


/**
 * Represents a Reversi game board.
 * By default board dimentions are 8*8, and game initialization is at center.
 *
 * It can show that matrix graphically and keeps track of the squares' locations.
 * It does not need to know a square's color and is not responsible for
 * maintaining changes in the square.
 * This allows for loose coupling and high cohesion.
 */
class Board {


	public:
		/**
		 * Enum for square/cell color, where black = 'X'. white = 'O'
		 */
		enum ElementInBoard {BLACK, WHITE, EMPTY};

		/**
		 * Default constructor, values are as demanded - 8*8
		 *
		 * @param size size of board
		 */
		Board(int size = 8);

		/**
		 * Destructor, since board size is decided during runtime.
		 */
		~Board();

		/**
		 * copy- constructor
		 */
		Board::Board(Board& other);

		/**
		 * Getter for size of board, which equals to number of columns and to number of rows
		 * @return  size of board
		 */
		int size() const;


		ElementInBoard** getBoard()const;

		/**
		 * Checks if the square in a given location is white.
		 * @param loc square's location
		 * @return true if square is white
		 */
		bool isCellWhite(const Location& loc) const;

		/**
		 * Checks if the square in a given location is black.
		 * @param loc square's location
		 * @return true if square is black
		 */
		bool isCellBlack(const Location& loc) const;

		/**
		 * Checks if the square in a given location is empty.
		 * @param loc square's location
		 * @return true if square is empty
		 */
		bool isCellEmpty(const Location& loc) const;

		/**
		 * Compares a the color of two given squares.
		 * @param loc1 location of square 1
		 * @param loc2 location of square 2
		 * @return true if the square colors are identical, and not empty
		 */
		bool compareCellColors(const Location& loc1, const Location& loc2) const;

		/**
		 * Compares a the color of a given square to given color.
		 * @param c color to compare square's color to
		 * @param loc location of square
		 * @return true if the colors are identical, and not empty
		 */
		bool compareCellColors(const ElementInBoard& c, const Location& loc) const;

		/**
		 * Turns an empty given location to given color.
		 * @param c color to make empty square
		 * @param loc location of square
		 * @throw logic_error if cell is not empty - cannot change color of a non-empty square
		 */
		void makeInColor(const ElementInBoard& c, const Location& loc);

		/**
		 * Changes the color in a given range by given jumps from from black to white and vice versa. TODO -needed?
		 *
		 * @param prevStart square before start of range
		 * @param end square of end of range
		 * @param rowJumps jumps with which to iterate on rows
		 * @param colJumps jumps with which to iterate on columns
		 */
		void flipColorInRange(const Location& prevStart, const Location& end, int rowJumps, int colJumps);

		/**
		 * Checks if a given loction is a part of board TODO -needed?
		 * @param loc location to check
		 * @return true if location is in range of board
		 */
		bool isInBoardRange(const Location& loc) const;


		/**
		 * Checks if location is at edge of board. TODO -needed?
		 * @param loc loaction to check
		 * @return true is location is an edge
		 */
		bool isEdge(const Location& loc) const;

		/**
		 * Checks if the board is full, by checking if there are no empty cells.
		 * @return true if there are no empty cells
		 */
		bool isBoardFull() const;

		/**
		 * Gets begin() iterator for the list of empty cells.
		 * @return iterator to the beginning of the empty cells list
		 */
		std::list<Location>::const_iterator emptyCellsBegin() const;

		/**
		 * Gets end() iterator for the list of empty cells.
		 * @return iterator to the end of the empty cells list
		 */
		std::list<Location>::const_iterator emptyCellsEnd() const;

	private:
		//size of board, cannot be changed after initialization
		const int size_;
		//pointer to matrix of enums representing board, will by dynamically allocated during runtime
		ElementInBoard** gameBoard_;
		//list of locations of empty cells in board
		std::list<Location> emptyCells_;

		/**
		 * Gets the square at a certain position on the board, for viewing only (square cannot be changed).
		 * This is a wrapping function for clarity of code that ensures safety in terms of changing a square.
		 *
		 * @param loc square's location on board
		 * @return wanted square
		 */
		const ElementInBoard& getCell(const Location& loc) const;

		/**
		 * Wrapping method for removing a location from the list of empty cells TODO-couldn't use - should remove?
		 * @param removalPoint location for removal
		 */
		void removeCellFromEmptyList(Location& removalPoint);
};

#endif /* BOARD_H_ */
