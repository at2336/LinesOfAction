#include "Game.h"
using namespace std;

Game::Game()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			gameBoard[i][j] = 0;
		}
	}
	for (int i = 1; i < 6; i++)
	{
		gameBoard[i][0] = 1;
		gameBoard[i][6] = 1;
		gameBoard[0][i] = 2;
		gameBoard[6][i] = 2;
	}
}

int Game::getPlayer()
{
	return playerColor;
}

void Game::restart()
{

}

void Game::setWhitePiecesNum(int num)
{
	whitePieces = num;
}

void Game::setBlackPiecesNum(int num)
{
	blackPieces = num;
}

int Game::getBlackPieces()
{
	return blackPieces;
}

int Game::getWhitePieces()
{
	return whitePieces;
}

void Game::checkWin()
{

}

void Game::playerMove(int pieceRow, int pieceCol, int moveRow, int moveCol)
{

}

void Game::capture()
{

}

void Game::aiMove()
{

}

int Game::getMovesRow(int pieceRow)
{
	int numMoves = 0;
	for (int i = 0; i < 7; i++)
	{
		if (gameBoard[pieceRow][i] != 0)
			numMoves++;
	}
	return numMoves;
}

int Game::getMovesCol(int pieceCol)
{
	int numMoves = 0;
	for (int i = 0; i < 7; i++)
	{
		if (gameBoard[i][pieceCol] != 0)
			numMoves++;
	}
	return numMoves;
}

bool Game::checkMove(int pieceRow, int pieceCol, int moveRow, int moveCol)
{
	bool canMove = false;
	int checkRow;
	int checkCol;
	int i = pieceRow;
	int j = pieceCol;
	if (pieceRow == moveRow)
		checkRow = getMovesRow(pieceRow);
	if (pieceCol == moveCol)
		checkCol = getMovesCol(pieceCol);
	while (i < pieceRow && j < pieceCol)
	{

	}
}

void Game::printBoard()
{
	if (playerColor < 1)
	{
		cout << "Select 1 for black and 2 for white: ";
		cin >> playerColor;
		if (playerColor == 1)
			aiColor = 2;
		else
			aiColor = 1;
	}
	for (int i = 0; i<7; i++)    //This loops on the rows.
	{
		for (int j = 0; j<7; j++) //This loops on the columns
		{
			cout << gameBoard[i][j] << " ";
		}
		cout << endl;
	}
}

