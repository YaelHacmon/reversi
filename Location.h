/*
 * Roni Fultheim, ID: 313465965
 * Location.h
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include <iostream>

/**
 * A location contains a row and a column of a square in the Board matrix.
 * Represents a point in a 2D space.
 */
class Location {
	public:
		/**
		 * C'tor of location.
		 * @param row row
		 * @param col column
		 */
		Location (int row, int col);

		/**
		 * Sets new row and column to location.
		 * @param row new row
		 * @param col new column
		 */
		void set(int row, int col);

		/**
		 * Sets new row and column to location
		 * @param loc location who's data to copy
		 */
		void set(Location& loc);

		/**
		 * Increments location's row and column by given numbers.
		 * @param incR how much to increment rows by
		 * @param incC how much to increment columns by
		 */
		void increment(int incR, int incC);

		/**
		 * Getter.
		 * @return column of location
		 */
		int column() const;

		/**
		 * Getter.
		 * @return row of location
		 */
		int row() const;

		/**
		 * Overloading of == operator for easy comparison
		 * @param loc other location to compare to
		 * @return true if both row and column of locations match
		 */
		bool operator ==(const Location &loc) const;

		/**
		 * Overloading of != operator for easy comparison
		 * @param loc other location to compare to
		 * @return true if either row or column of locations do not match
		 */
		bool operator !=(const Location &loc) const;

		/**
		 * Overloading of << for easy printing, using friend function.
		 * @param out output stream
		 * @param loc location to print
		 * @return output stream with printed location
		 */
		friend std::ostream &operator <<(std::ostream &out, const Location &loc);

	private:
		int row_;
		int col_;
};


#endif /* LOCATION_H_ */
