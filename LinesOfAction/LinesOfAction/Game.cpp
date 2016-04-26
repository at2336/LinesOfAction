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
	if(true)
	{ }
}

bool Game::playerMove(int pieceRow, int pieceCol, int moveRow, int moveCol)
{
	if (gameBoard[pieceRow][pieceCol] == playerColor && checkMove(pieceRow, pieceCol, moveRow, moveCol) && gameBoard[moveRow][moveCol] == 0)
	{
		gameBoard[moveRow][moveCol] = gameBoard[pieceRow][pieceCol];
		gameBoard[pieceRow][pieceCol] = 0;
		return true;
	}
	else if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && gameBoard[moveRow][moveCol] == aiColor)
	{
		capture(pieceRow, pieceCol, moveRow, moveCol);
		return true;
	}
	else
	{
		cout << "Not possible! Make another move. \n";
		return false;
	}
}

 bool Game::ifBlocked(int pieceRow, int pieceCol, int moveRow, int moveCol)
{
	bool blocked = false;
	int i = pieceRow;
	int j = pieceCol;
	if (pieceRow - moveRow > 0)
	{
		int spaceDiffRow = pieceRow - moveRow;
		while (spaceDiffRow != 0)
		{
			if (gameBoard[i--][pieceCol] == aiColor && spaceDiffRow > 1)
			{
				return true;
			}
			spaceDiffRow--;
		}
	}
	else if (pieceCol - moveCol > 0)
	{
		int spaceDiffCol = pieceCol - moveCol;
		while (spaceDiffCol != 0)
		{
			if (gameBoard[pieceRow][j--] == aiColor && spaceDiffCol > 1)
			{
				return true;
			}
			spaceDiffCol--;
		}
	}
	else if (pieceRow - moveRow < 0)
	{
		int spaceDiffRow = moveRow - pieceRow;
		while (spaceDiffRow != 0)
		{
			if (gameBoard[i++][pieceCol] == aiColor && spaceDiffRow > 1)
			{
				return true;
			}
			spaceDiffRow++;
		}
	}
	else if (pieceCol - moveCol < 0)
	{
		int spaceDiffCol = pieceCol - moveCol;
		while (spaceDiffCol != 0)
		{
			if (gameBoard[pieceRow][j++] == aiColor && spaceDiffCol > 1)
			{
				return true;
			}
			spaceDiffCol++;
		}
	}
	return false;
}

void Game::capture(int pieceRow, int pieceCol, int moveRow, int moveCol)
{
	if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && gameBoard[moveRow][moveCol] != gameBoard[pieceRow][pieceCol] && gameBoard[moveRow][moveCol] != 0)
	{
		int i = gameBoard[moveRow][moveCol];
		gameBoard[moveRow][moveCol] = gameBoard[pieceRow][pieceCol];
		gameBoard[pieceRow][pieceCol] = 0;
		if (i == 1)
			blackPieces--;
		else
			whitePieces++;
	}
}

void Game::aiMove()
{

}

int Game::getMovesRow(int pieceCol)
{
	int numMoves = 0;
	for (int i = 0; i < 7; i++)
	{
		if (gameBoard[i][pieceCol] != 0)
			numMoves++;
	}
	return numMoves;
}

int Game::getMovesCol(int pieceRow)
{
	int numMoves = 0;
	for (int i = 0; i < 7; i++)
	{
		if (gameBoard[pieceRow][i] != 0)
			numMoves++;
	}
	return numMoves;
}

bool Game::checkMove(int pieceRow, int pieceCol, int moveRow, int moveCol)
{
	bool checkRow = false;
	bool checkCol = false;
	int i = pieceRow;
	int j = pieceCol;
	bool checkDiag = false;
	if (pieceCol == moveCol)
	{
		int numRowMoves = getMovesRow(pieceCol);
		if (numRowMoves >= abs(pieceRow - moveRow))
			checkRow = true;
	}
	else if (pieceRow == moveRow)
	{
		int numColMoves = getMovesCol(pieceRow);
		if (numColMoves >= abs(pieceCol - moveCol))
			checkCol = true;
	}
	else if ((pieceCol + moveCol + pieceRow + moveRow) % 2 == 0)
	{
		while (i > 2 && i < 7 && j > 2 && j < 7)
		{
			if (gameBoard[i--][j--] != 0)
				checkDiag = true;
		}
		while (i >= 0 && i < 7 && j >= 0 && j < 7)
		{
			if (gameBoard[i++][j++] != 0)
				checkDiag = true;
		}
	}
	if (checkRow || checkCol || checkDiag)
		return true;
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
	for (int k = 0; k < 7; k++)
	{
		if (k > 0)
			cout << " " << k;
		else
			cout << "  " << k;
	}
	cout << "\n";
	for (int i = 0; i<7; i++)    //This loops on the rows.
	{
		cout << i << " ";
		for (int j = 0; j<7; j++) //This loops on the columns
		{
			cout << gameBoard[i][j] << " ";
		}
		cout << endl;
	}
}
int Game::getWin()
{
	return win;
}