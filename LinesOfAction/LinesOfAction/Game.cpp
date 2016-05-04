#include "Game.h"
#include <vector>
using namespace std;

Game::Game()  //constructor for game
{
	win = 0;
	blackPieces = 3;
	whitePieces = 3;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gameBoard[i][j] = 0;
		}
	}
	for (int i = 1; i < 4; i++)
	{
		gameBoard[i][0] = 1;
		gameBoard[i][4] = 1;
		gameBoard[0][i] = 2;
		gameBoard[4][i] = 2;
	}
}

int Game::getPlayer()  //returns player's color
{
	return playerColor;
}

int Game::getAI()  //returns AI's color
{
	return aiColor;
}

void Game::setCurrentTurn(int turn)  //set the current color's turn
{
	currentTurn = turn;
}

int Game::getCurrentTurn() //returns the current player's turn
{
	return currentTurn;
}

void Game::restart()  //restarts the game
{
	system("cls");
	Game();
	win = 0;
	aiColor = NULL;
	playerColor = NULL;
	currentTurn = 0;
}

void Game::setWhitePiecesNum(int num)  //Sets the number of white pieces
{
	whitePieces = num;
}

void Game::setBlackPiecesNum(int num)  //Sets the number of black pieces
{
	blackPieces = num;
}

int Game::getBlackPieces()  //Returns the number of black pieces
{
	return blackPieces;
}

int Game::getWhitePieces()  //Returns the number of white pieces
{
	return whitePieces;
}

void Game::checkWin()  //Checks if some won
{
	if(whitePieces == 1)
		win = 2;
	else if(blackPieces == 1)
		win = 1;

}

bool Game::playerMove()  //Make the player move
{
	cout << "Please enter the row of the piece you would like to move: ";
	cin >> pieceRow;
	cout << "Please enter the col of the piece you would like to move: ";
	cin >> pieceCol;
	cout << "Please enter the row of where you would like to move: ";
	cin >> moveRow;
	cout << "Please enter the col of where you would like to move: ";
	cin >> moveCol;
	if (currentTurn == playerColor && gameBoard[pieceRow][pieceCol] == playerColor 
		&& !ifBlocked(pieceRow, pieceCol, moveRow, moveCol) 
		&& checkMove(pieceRow, pieceCol, moveRow, moveCol) 
		&& gameBoard[moveRow][moveCol] == 0)
	{
		gameBoard[moveRow][moveCol] = gameBoard[pieceRow][pieceCol];
		gameBoard[pieceRow][pieceCol] = 0;
		checkWin();
		setCurrentTurn(getAI());
		return true;
	}
	else if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && gameBoard[moveRow][moveCol] == aiColor)
	{
		capture(pieceRow, pieceCol, moveRow, moveCol);
		checkWin();
		setCurrentTurn(getAI());
		return true;
	}
	else
	{
		cout << "Not possible! Make another move. \n";
		return false;
	}
}

 bool Game::ifBlocked(int pieceRow, int pieceCol, int moveRow, int moveCol)  //Checks if a piece is blocked when attempting to make move
{
	bool blocked = false;
	int i = pieceRow;
	int j = pieceCol;
	if (pieceRow - moveRow > 0 && pieceCol == moveCol)
	{
		int spaceDiffRow = pieceRow - moveRow;
		while (spaceDiffRow != 0)
		{
			if (gameBoard[--i][pieceCol] == aiColor && spaceDiffRow > 1)
			{
				return true;
			}
			spaceDiffRow--;
		}
	}
	else if (pieceCol - moveCol > 0 && pieceRow == moveRow)
	{
		int spaceDiffCol = pieceCol - moveCol;
		while (spaceDiffCol != 0)
		{
			if (gameBoard[pieceRow][--j] != getCurrentTurn() && gameBoard[pieceRow][j] != 0 && spaceDiffCol > 1)
			{
				return true;
			}
			spaceDiffCol--;
		}
	}
	else if (pieceRow - moveRow < 0 && pieceCol == moveCol)
	{
		int spaceDiffRow = abs(pieceRow - moveRow);
		while (spaceDiffRow != 0)
		{
			if (gameBoard[++i][pieceCol] != getCurrentTurn() && gameBoard[i][pieceCol] != 0 && spaceDiffRow > 1)
			{
				return true;
			}
			spaceDiffRow--;
		}
	}
	else if (pieceCol - moveCol < 0 && pieceRow == moveRow)
	{
		int spaceDiffCol = abs(pieceCol - moveCol);
		while (spaceDiffCol != 0)
		{
			if (gameBoard[pieceRow][++j] != getCurrentTurn() && gameBoard[pieceRow][j] != 0 && spaceDiffCol > 1)
			{
				return true;
			}
			spaceDiffCol--;
		}
	}
	else if (pieceRow > moveRow && pieceCol < moveCol)
	{
		while(--i != moveRow && ++j != moveCol)
		{
			if (gameBoard[i][j] != getCurrentTurn() && gameBoard[i][j] != 0)
				return true;
		}
	}
	else if (pieceRow > moveRow && pieceCol > moveCol)
	{
		while (--i != moveRow && --j != moveCol)
		{
			if (gameBoard[i][j] != getCurrentTurn() && gameBoard[i][j] != 0)
				return true;
		}
	}
	else if (pieceRow < moveRow && pieceCol < moveCol)
	{
		while (++i != moveRow && ++j != moveCol)
		{
			if (gameBoard[i][j] != getCurrentTurn() && gameBoard[i][j] != 0)
				return true;
		}
	}
	else if (pieceRow < moveRow && pieceCol > moveCol)
	{
		while (++i != moveRow && --j != moveCol)
		{
			if (gameBoard[i][j] != getCurrentTurn() && gameBoard[i][j] != 0)
				return true;
		}
	}
	return false;
}

void Game::capture(int pieceRow, int pieceCol, int moveRow, int moveCol) //Captures an enemy piece
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

void Game::aiMove()  //AI's turn. Calculates all possible moves and chooses best one
{
	calculateAllMoves();
	outputMoves();
}

void Game::calculateAllMoves()  //Calculates all possible moves based on board
{
	allMoves.clear();
	vector<pair<int, int>> allPieces;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (gameBoard[i][j] == aiColor)
				allPieces.push_back(make_pair(i, j));
		}
	}
	int k = 0;
	
	for( vector<pair<int,int>>::iterator boardIt = allPieces.begin(); boardIt != allPieces.end(); ++boardIt)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				int tempX = boardIt->first;
				int tempY = boardIt->second;
				if(checkMove(tempX, tempY, i, j) && !ifBlocked(tempX, tempY, i,j) && gameBoard[i][j] != aiColor)
				{
					string move = to_string(tempX) + to_string(tempY) + to_string(i) + to_string(j);
					allMoves.push_back(move);
				}
			}
		}
	}
}

void Game::outputMoves()  //Outputs list of moves
{
	for(int i = 0; i < allMoves.size();i++)
	{
		cout << allMoves[i] << endl;
	}
	cout << allMoves.size() << endl;
}

void Game::lastMovedPiece(int pieceRow, int pieceCol)  //Stores the last moved piece 
{
	 lastMoved = to_string(pieceRow) + to_string(pieceCol);
}

int Game::getMovesRow(int pieceCol) //Gets the number of steps possible horizontally for a piece
{
	int numMoves = 0;
	for (int i = 0; i < 5; i++)
	{
		if (gameBoard[i][pieceCol] != 0)
			numMoves++;
	}
	return numMoves;
}

int Game::getMovesCol(int pieceRow)  //Returns the number of steps possible vertically for a piece
{
	int numMoves = 0;
	for (int i = 0; i < 5; i++)
	{
		if (gameBoard[pieceRow][i] != 0)
			numMoves++;
	}
	return numMoves;
}

int Game::getMovesDiag(int pieceRow, int pieceCol, int moveRow, int moveCol)  //returns the number of steps possible diagonally
{
	diagMoves = 0;
	int i = pieceRow;
	int j = pieceCol;
	if(pieceRow < moveRow && pieceCol < moveCol) //lower right
	{
		if (i == 0 || j == 0 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 0 && i <= 5 && j > 0 && j <= 5)
		{
			if (gameBoard[i--][j--] != 0)
				diagMoves++;
		}
		int i = pieceRow;
		int j = pieceCol;
		if (i == 5 || j == 5 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 0 && i < 5 && j >= 0 && j < 5)
		{
			if (gameBoard[++i][++j] != 0)
			{
				diagMoves++;
			}
		}
	}
	else if(pieceRow < moveRow && pieceCol > moveCol) //lower left
	{
		if(i == 0 || j == 5 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 0 && i <= 5 && j >= 0 && j < 5)
		{
			if (gameBoard[i--][j++] != 0)
				diagMoves++;
		}
		int i = pieceRow;
		int j = pieceCol;
		if(i == 5 || j == 0 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 0 && i < 5 && j > 0 && j <= 5)
		{
			if (gameBoard[++i][--j] != 0)
				diagMoves++;
		}
	}
	else if(pieceRow > moveRow && pieceCol < moveCol) //upper right
	{
		if(i == 5 || j == 0 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 0 && i < 5 && j > 0 && j <= 5)
		{
			if (gameBoard[i++][j--] != 0)
			{
				diagMoves++;
			}
		}
		int i = pieceRow;
		int j = pieceCol;
		if(i == 0 || j == 5 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 1 && i <= 5 && j > 0 && j < 5)
		{
			if (gameBoard[--i][++j] != 0)
			{
					diagMoves++;
			}
		}
	}
	else if(pieceRow > moveRow && pieceCol > moveCol) //upper left
	{
		if(i == 5 || j == 5 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 0 && i < 5 && j >= 0 && j < 5)
		{
			if (gameBoard[i++][j++] != 0)
				diagMoves++;
		}
		int i = pieceRow;
		int j = pieceCol;
		if(i == 0 || j == 0 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 0 && i <= 5 && j > 0 && j <= 5)
		{
			if (gameBoard[--i][--j] != 0)
				diagMoves++;
		}
	}
	return diagMoves;
}

bool Game::checkMove(int pieceRow, int pieceCol, int moveRow, int moveCol) //Checks if such a move is possible based on # of pieces & position
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
		if(abs(pieceRow - pieceCol) == abs(moveRow - moveCol) && pieceRow > moveRow && pieceCol > moveCol) //upper left
		{
			int spaceDiff = abs(pieceRow - moveRow);
			int x = getMovesDiag(pieceRow, pieceCol, moveRow, moveCol);
			if(spaceDiff <= x)
				return true;
		}
		else if(pieceRow + pieceCol == moveRow + moveCol && pieceRow > moveRow) //bottom left
		{
			int spaceDiff = abs(pieceRow - moveRow);
			int x = getMovesDiag(pieceRow, pieceCol, moveRow, moveCol);
			if(spaceDiff <= x)
				return true;
		}
		else if(pieceRow + pieceCol == moveRow + moveCol && pieceRow < moveRow) //upper right
		{
			int spaceDiff = abs(pieceRow - moveRow);
			int x = getMovesDiag(pieceRow, pieceCol, moveRow, moveCol);
			if(spaceDiff <= x)
				return true;
		}
		else if(abs(pieceRow - moveRow) == abs(pieceCol - moveCol) && pieceRow < moveRow) //bottom right
		{
			int spaceDiff = abs(pieceRow - moveRow);
			int x = getMovesDiag(pieceRow, pieceCol, moveRow, moveCol);
			if(spaceDiff <= x)
				return true;
		}
	}
	if (checkRow || checkCol || checkDiag)
		return true;
}

void Game::printBoard()  //prints the board
{
	if (playerColor < 1)
	{
		cout << "Select 1 for black and 2 for white: ";
		cin >> playerColor;
		if (playerColor == 1)
		{
			aiColor = 2;
			currentTurn = playerColor;
		}
		else
		{
			aiColor = 1;
			currentTurn = aiColor;
		}
	}
	for (int k = 0; k < 5; k++)
	{
		if (k > 0)
			cout << " " << k;
		else
			cout << "  " << k;
	}
	cout << "\n";
	for (int i = 0; i<5; i++)    //This loops on the rows.
	{
		cout << i << " ";
		for (int j = 0; j<5; j++) //This loops on the columns
		{
			cout << gameBoard[i][j] << " ";
		}
		cout << endl;
	}
}
int Game::getWin()  //Returns the winner's color
{
	return win;
}