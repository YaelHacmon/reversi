/*
 * GameManager.cpp
 */

#include "../include/GameManager.h"

using namespace std;

GameManager::GameManager(ViewGame* view, Board& b, Player* black, Player* white, MoveLogic* log):
														board_(b), currPlayer_(black), oppPlayer_(white), logic_(log), view_(view) {}


GameManager::~GameManager() {}

void GameManager::showWinner()
{
	if (currPlayer_->getScore() > oppPlayer_->getScore()) {
		view_->messageWinner(currPlayer_->getName());
	}
	else if (currPlayer_->getScore() < oppPlayer_->getScore())
	{
		view_->messageWinner(oppPlayer_->getName());
	}
	else
	{
		view_->showMessage("Game over! Tie!! Players have equal scores.");
	}
}
