#include "../include/ViewByConsole.h"
#include <iostream>
#include <string>
using namespace std;

void ViewByConsole::printBoard(Board::ElementInBoard** board, int sizeOfBoard) const
{
	//print the indexes of the columns
	cout << " | ";
	for(int i=1; i<=sizeOfBoard ;++i)
	{
		cout << i << " | ";
	}
	cout << endl;
	// print spaces line
	cout << "----------------------------------" << endl;
	// print the content of the board
	for(int i=0; i<sizeOfBoard ;++i)
	{
		// the index of the line
		cout << i+1 << "|";
		for(int j=0; j<sizeOfBoard; ++j)
		{
			switch(board[i][j])
			{
			case Board::BLACK:
				cout << " X |";
				break;
			case Board::WHITE:
				cout << " O |";
				break;
			case Board::EMPTY:
				cout << "   |";
				break;
			default:
				break;
			}

		}
		cout << endl;
		// print spaces line
		cout << "----------------------------------" << endl;
	}
}

void ViewByConsole::messageForTurn(string curPlayer) const
{
	cout<<curPlayer<<": It's your move"<< endl;
}

void ViewByConsole::messagePossibleMoves(const vector<Location> &possibleMoves) const
{
	int possibleMovesSize = possibleMoves.size();
	cout<<"Your possible moves: ";
	for (int i=0; i<possibleMovesSize; ++i)
	{
		cout << possibleMoves[i];
		if( i == possibleMovesSize-1)
		{
			cout << endl;
		}
		else
		{
			cout << ",";
		}
	}
}

Location ViewByConsole::getMoveFromUser() const
{
	int row;
	int col;

	//get player's move
	cin >> row;
	cin >> col;

	// input validation: while the input is not valid - keep asking for valid one
	while(cin.fail())
	{
		showMessage("Invalid move format, please try again! Enter your move row,col: ");
		cin.clear();
		cin.ignore();
		cin >> row;
		cin >> col;
	}

	return Location(row-1,col-1);
}


void ViewByConsole::messageWinner(string winPlayer) const
{
	cout << "Game over! " << winPlayer << " has won the game!" << endl;
}


void ViewByConsole::showMessage(string stringToShow) const
{
	cout<<stringToShow<<endl;
}


void ViewByConsole::messagePlayerMove(Location pointToDisplay, string curPlayer)const
{
	cout<<curPlayer<<" played "<< pointToDisplay << endl;
}


void ViewByConsole::messageSwitchTurns() const
{
	showMessage("No possible moves. Play passes to the other player. Press any key to continue.");
	char anyKey;
	cin >> anyKey;
}


int ViewByConsole::presentMenu(const vector<string>& menuOpps) const
{
	//show menu title
	showMessage(menuOpps[0]);

	//go over options vector to show options
	for (int i=1; i < menuOpps.size(); i++)
	{
		//show option and index
		cout << "To " << menuOpps[i] << ", press " << (i) << endl;
	}

	//get player's choice
	int choice;
	cin >> choice;

	// input validation: while the input is not valid- keep asking for valid one
	//input is not valid if it is either not a number, or is not in range of given options [1-size]
	while(cin.fail() || choice<1 || choice > menuOpps.size())
	{

		showMessage("Choice must be a number from given options, please try again:");
		cin.clear();
		cin.ignore();
		cin >> choice;
	}

	//translate choice back to c++ indexing and return it
	return choice;
}
