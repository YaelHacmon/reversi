/*
 * LocalGameManager.cpp
 */

#include "../include/LocalGameManager.h"

LocalGameManager::LocalGameManager(ViewGame* view, Board& b, Player* black,
		Player* white, MoveLogic* log): GameManager(view, b, black, white, log) {}


void LocalGameManager::playGame() {
	//declare flag - in first turn game has not been played, current player has moves
	bool noMoves = false;

	view_->showMessage("Current board:");
	view_->printBoard(board_.getBoard(), board_.size());

	/* General explanation - First, build a list containing all the
	 * empty cells on the board. then, checking what might be a possible
	 * move dor the player, and putting all the options into a vector.
	 * The user select a point, and the board update acoording to the
	 *  selected point.
	 */

	//while game is not over - keep playing
	while (!board_.isBoardFull())
	{
		//display current turn
		view_->messageForTurn(currPlayer_->getName());

		//initialize moves for black and white players
		logic_->updateMoveOptions(currPlayer_, board_);

		//declare move here - so we can show move later
		Location move(-1,-1);

		//if current player can play his turn
		if (logic_->canPlayTurn(currPlayer_)) {
			//show possible moves
			view_->messagePossibleMoves(currPlayer_->getPossibleMoves());

			//get next player's move
			move = currPlayer_->getNextMove(view_, logic_, board_,oppPlayer_);

			//check that move is allowed
			//while move isn't legal - get another move from player
			while (!logic_->isMoveAllowed(move, currPlayer_))
			{
				view_->showMessage("Illegal move, try again.");
				move = currPlayer_->getNextMove(view_, logic_, board_,oppPlayer_);
			}

			//call logic to play move
			logic_->playMove(move, currPlayer_, board_, oppPlayer_);

			//update flag
			noMoves = false;
		}
		//if current player cannot play his turn
		else
		{
			//if the second player cannot play - show message and switch turns
			if (!noMoves) {
				view_->messageSwitchTurns();
				noMoves = true;

			}
			else
			{
				//if both players did not play - game is over, there are no more moves left in game
				view_->showMessage("No possible moves for both players.");
				break;
			}
		}

		//show board and last moves
		view_->showMessage("\nCurrent board:");
		view_->printBoard(board_.getBoard(), board_.size());
		//message of last turn - if was played
		if (!noMoves) {
			view_->messagePlayerMove(move, currPlayer_->getName());
		}

		//switch players
		Player* temp = currPlayer_;
		currPlayer_ = oppPlayer_;
		oppPlayer_ = temp;
	}
	showWinner();
}
