/*
 * Yael Hacmon, ID 313597897
 * Roni Fultheim, ID 313465965
 */

#include "Player.h"

Player::Player(const std::string& name, const ColorOfPlayer& c): name_(name), color_(c), score_(2){
	possibleMoves_ = std::vector<Location>();
}

Player::Player(const Player& other): name_(other.getName()), color_(other.getColor()), score_(other.getScore()) {};

//empty destructor
Player::~Player() {}

Player::ColorOfPlayer Player::getColor() const {
	return color_;
}


const std::string& Player::getName() const {
	return name_;
}


int Player::getScore() const {
	return score_;
}


const std::vector<Location>& Player::getPossibleMoves() const {
	return possibleMoves_;
}


bool Player::hasPossibleMoves() const {
	//check if vector is empty - and return the opposite answer: true if possible moves exist, meaning vector is non-empty
	return !possibleMoves_.empty();
}


void Player::updatePossibleMoves(const std::vector<Location>& locs) {
	//use copy constructor to copy the given vector to data member
	//vector copies its internal elements as well - allows
	possibleMoves_ = locs;
}


// if current Player "ate" the opposite Player - the opposite Player's score decreases
void Player::decreaseScore (int toDecrease) {
	score_ = score_ - toDecrease;
}

// if current Player "ate" the opposite Player - the opposite Player's score increases
void Player::increaseScore (int toIncrease) {
	score_ = score_ + toIncrease;
}
