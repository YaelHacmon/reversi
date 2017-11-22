/*
 * Roni Fultheim, ID: 313465965
 * Location.cpp
 */

#include "Location.h"

using namespace std;

Location::Location (int row, int col): row_(row), col_(col) {}

void Location::set(int row, int col) {
	row_ = row;
	col_ = col;
}

void Location::set(Location& loc) {
	set(loc.row(), loc.column());
}

void Location::increment(int incR, int incC) {
	row_ += incR;
	col_ += incC;
}

int Location::column() const {
	return col_;
}

int Location::row() const {
	return row_;
}

bool Location::operator ==(const Location &loc) const {
	//compare rows and columns
	return (loc.row() == row_ && loc.column() == col_);
}

bool Location::operator !=(const Location &loc) const {
	//use == operator for
	return !(*this==loc);
}

ostream &operator <<(ostream &out, const Location &loc)
{
	//translate from c++ indexing
	out << "(" << loc.row_+1 << "," << loc.col_+1 << ")";
	return out;
}

