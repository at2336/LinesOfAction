//Source file for the game

#include "Game.h"
#include <queue>
#include <list>
#include <algorithm>

using namespace std;

Game::Game()  //constructor for game. Creates the board and initializes the number of starting piecces. The num of pieces can be changed for a smaller or larger game
{
	win = 0;
	blackPieces = 6;
	whitePieces = 6;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gameBoard[i][j] = 0;
		}
	}
	for (int i = 1; i < ROWS - 1; i++)
	{
		gameBoard[i][0] = 1;
		gameBoard[i][ROWS - 1] = 1;
		gameBoard[0][i] = 2;
		gameBoard[ROWS - 1][i] = 2;
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

int Game::evaluate(int tempBoard[ROWS][COLS]) //Evaluation function used for alpha-beta. calculates value based on max distance and nodes
{
	list<pair<int, int>> myList;
	int pieceColor = getAI();
	int numPieces;
	if (pieceColor == 1)
		numPieces = getBlackPieces();
	else
		numPieces = getWhitePieces();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (tempBoard[i][j] == pieceColor)
				myList.push_back(make_pair(i, j));
		}
	}
	int count = 1;
	int distance = 0;
	int maxDist = INT_MIN;
	while (!myList.empty())
	{
		pair<int, int> firstElement;
		pair<int, int> secondElement;
		firstElement = myList.front();
		myList.pop_front();
		if (myList.size() > 0)
			secondElement = myList.front();
		if (abs((firstElement.first) - secondElement.first) >= 1 || abs((firstElement.second) - secondElement.second) >= 1 ||
			((abs((firstElement.first) - secondElement.first) >= 1 && abs((firstElement.second) - secondElement.second)) >= 1))
			distance = abs((firstElement.first) - secondElement.first) + abs((firstElement.second) - secondElement.second);
		if (distance > maxDist)
			maxDist = distance;
	}
	return -1 * (maxDist * 10);
}

pair<pair<int, int>,pair<int,int>> Game::alphaBeta() //Alphabeta search used for AI to move
{
	nodes = 0;
	maxEval = 0;
	minEval = 0;
	minPrune = 0;
	maxPrune = 0;
	pair<pair<int,int>,pair<int,int>> maxValue = action(INT_MIN, INT_MAX, 0);
	cout << "Maxmum depth: " << maxDepth << endl;
	cout << "Nodes generated: " << nodes << endl;
	cout << "Number of times evaluation was called from min-value: " << minEval << endl;
	cout << "Number of times evaluation was called from max-value: " << maxEval << endl;
	cout << "Number of times pruning occured from min-value: " << minPrune << endl;
	cout << "Number of times pruning occured from max-value: " << maxPrune << endl;
	return maxValue;
}

pair<pair<int,int>,pair<int,int>> Game::action(int maxUtil, int minUtil, int depth) //Decides what the AI should do 
{
	timer = clock();
	int value = INT_MIN;
	int alpha = maxUtil;
	int beta = minUtil;
	int pieceRow;
	int pieceCol;
	int moveRow;
	int moveCol;
	int tempBoard[ROWS][COLS];
	pair<pair<int,int>, pair<int,int>> bestMove;
	vector<pair<pair<int, int>, pair<int, int>>> allMoves = calculateAllMoves();
	for (int x = 0; x < allMoves.size(); x++)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				tempBoard[i][j] = gameBoard[i][j];
			}
		}
		int val = value;
		pieceRow = allMoves[x].first.first;
		pieceCol = allMoves[x].first.second;
		moveRow = allMoves[x].second.first;
		moveCol = allMoves[x].second.second;
		movePiece(tempBoard, pieceRow, pieceCol, moveRow, moveCol);
		maxDepth++;
		nodes++;
		value = max(value, minVal(tempBoard, alpha, beta, depth+1));
		if (value > val)
			bestMove = allMoves[x];
		alpha = max(alpha, value);
	}
	return bestMove;
}

int Game::maxVal(int tempBoard[ROWS][COLS], int alpha, int beta, int depth) //Searches for max value in alpha-beta. Creates a temp board and plays all possible moves
{
	if (checkAIWin(tempBoard))
		return 100;
	else if (checkPlayerWin(tempBoard))
		return -100;
	if (clock() - timer > 500)
	{
		maxEval++;
		return evaluate(tempBoard);
	}
	int value = INT_MIN;
	int pieceRow;
	int pieceCol;
	int moveRow;
	int moveCol;
	int tempBoard2[ROWS][COLS];
	vector<pair<pair<int, int>, pair<int, int>>> allMoves = calculateAllMoves();
	for (int x = 0; x < allMoves.size(); x++)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				tempBoard2[i][j] = tempBoard[i][j];
			}
		}
		pieceRow = allMoves[x].first.first;
		pieceCol = allMoves[x].first.second;
		moveRow = allMoves[x].second.first;
		moveCol = allMoves[x].second.second;
		movePiece(tempBoard2, pieceRow, pieceCol, moveRow, moveCol);
		maxDepth++;
		nodes++;
		value = max(value, minVal(tempBoard2, alpha, beta, depth+1));
		if (value >= beta)
		{
			maxPrune++;
			return value;
		}
		alpha = max(alpha, value);
	}
	return value;
}

int Game::minVal(int tempBoard[ROWS][COLS], int alpha, int beta, int depth) //Searches for min-value in alpha beta. Creates a temp board and plays all possible moves
{
	if (checkAIWin(tempBoard))
		return 100;
	if (checkPlayerWin(tempBoard))
		return -100;
	if (clock() - timer > 500) //Timer used to calculate when to do evaluate function. Set to 7 seconds because of stack overflow issues
	{
		minEval++;
		return evaluate(tempBoard);
	}
	int value = INT_MAX;
	int pieceRow;
	int pieceCol;
	int moveRow;
	int moveCol;
	int tempBoard1[ROWS][COLS];
	vector<pair<pair<int, int>, pair<int, int>>> allMoves = calculateAllMovesPlayer();
	for (int x = 0; x < allMoves.size(); x++)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				tempBoard1[i][j] = tempBoard[i][j];
			}
		}
		pieceRow = allMoves[x].first.first;
		pieceCol = allMoves[x].first.second;
		moveRow = allMoves[x].second.first;
		moveCol = allMoves[x].second.second;
		movePiece(tempBoard1, pieceRow, pieceCol, moveRow, moveCol);
		depth++;
		value = min(value, maxVal(tempBoard1, alpha, beta, depth+1));
		if (value <= alpha)
		{
			minPrune++;
			return value;
		}
		beta = min(beta, value);
	}
	return value;
}

bool Game::checkAIWin(int tempBoard[ROWS][COLS])  //Checks if the AI's board is a winning board. Used as terminal test for alpha beta search
{
	list<pair<int, int>> myList;
	int pieceColor = getAI();
	int numPieces;
	if (pieceColor == 1)
		numPieces = getBlackPieces();
	else
		numPieces = getWhitePieces();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (tempBoard[i][j] == pieceColor)
				myList.push_back(make_pair(i, j));
		}
	}
	int count = 1;
	while (!myList.empty())
	{
		pair<int, int> firstElement;
		pair<int, int> secondElement;
		firstElement = myList.front();
		myList.pop_front();
		if (myList.size() > 0)
			secondElement = myList.front();
		if (abs((firstElement.first) - secondElement.first) == 1 || abs((firstElement.second) - secondElement.second) == 1 ||
			((abs((firstElement.first) - secondElement.first) == 1 && abs((firstElement.second) - secondElement.second)) == 1))
		{
			count++;
			if (count == numPieces)
				return true;
		}
		else
			count = 1;
	}
	return false;
}

bool Game::checkPlayerWin(int tempBoard[ROWS][COLS])  //Checks if player won. Terminal test for alpha beta search
{
	list<pair<int, int>> myList;
	int pieceColor = getPlayer();
	int numPieces;
	if (pieceColor == 1)
		numPieces = getBlackPieces();
	else
		numPieces = getWhitePieces();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (tempBoard[i][j] == pieceColor)
				myList.push_back(make_pair(i, j));
		}
	}
	int count = 1;
	while (!myList.empty())
	{
		pair<int, int> firstElement;
		pair<int, int> secondElement;
		firstElement = myList.front();
		myList.pop_front();
		if (myList.size() > 0)
			secondElement = myList.front();
		if (abs((firstElement.first) - secondElement.first) == 1 || abs((firstElement.second) - secondElement.second) == 1 ||
			((abs((firstElement.first) - secondElement.first) == 1 && abs((firstElement.second) - secondElement.second)) == 1))
		{
			count++;
			if (count == numPieces)
			{
				return true;
			}
		}
		else
			count = 1;
	}
	return false;
}

void Game::checkWin()  //Checks if someone won. Used for both players
{
	list<pair<int,int>> myList;
	int pieceOne = lastMoved.first;
	int pieceTwo = lastMoved.second;
	int pieceColor = gameBoard[pieceOne][pieceTwo];
	int numPieces;
	int numPiecesOther;
	int otherPlayer;
	if (pieceColor == 1)
	{
		otherPlayer = 2;
		numPieces = getBlackPieces();
		numPiecesOther = getWhitePieces();
	}
	else
	{
		otherPlayer = 1;
		numPieces = getWhitePieces();
		numPiecesOther = getBlackPieces();
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (gameBoard[i][j] == pieceColor)
				myList.push_back(make_pair(i, j));
		}
	}
	int count = 1;
	while (!myList.empty())
	{
		pair<int,int> firstElement;
		pair<int, int> secondElement;
		firstElement = myList.front();
		myList.pop_front();
		if (myList.size() > 0)
			secondElement = myList.front();
		if ((abs(firstElement.first - secondElement.first) == 1 && firstElement.second == secondElement.second)
			|| (abs(firstElement.second - secondElement.second) == 1 && firstElement.first == secondElement.first)
			|| (abs(firstElement.first - secondElement.first) == 1 && abs(firstElement.second - secondElement.second) == 1))
		{
			count++;
			if (pieceColor == 1 && count == numPieces)
			{
				win = 1;
				cout << win << " has won the game!" << endl;
			}
			if (pieceColor == 2 && count == numPieces)
			{
				win = 2;
				cout << win << " has won the game!" << endl;
			}
		}
		else
			count = 1;
	}
	if (whitePieces == 1)
	{
		win = 2;
		cout << win << " has won the game" << endl;;
	}
	else if (blackPieces == 1)
	{
		win = 1;
		cout << win << " has won the game" << endl;
	}
	
	//Check other player. Primarily used when a player captures and checks if the other player has the pieces in a contiguous fashion
	list<pair<int, int>> myListOther;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (gameBoard[i][j] == otherPlayer)
				myListOther.push_back(make_pair(i, j));
		}
	}
	int countOther = 1;
	while (!myListOther.empty())
	{
		pair<int, int> firstElementOther;
		pair<int, int> secondElementOther;
		firstElementOther = myListOther.front();
		myListOther.pop_front();
		if (myListOther.size() > 0)
			secondElementOther = myListOther.front();
		if ((abs(firstElementOther.first - secondElementOther.first) == 1 && firstElementOther.second == secondElementOther.second)
			|| (abs(firstElementOther.second - secondElementOther.second) == 1 && firstElementOther.first == secondElementOther.first)
			|| (abs(firstElementOther.first - secondElementOther.first) == 1 && abs(firstElementOther.second - secondElementOther.second) == 1))
		{
			countOther++;
			if (otherPlayer == 1 && countOther == numPiecesOther)
			{
				win = 1;
				cout << win << " has won the game!" << endl;
			}
			if (otherPlayer == 2 && countOther == numPiecesOther)
			{
				win = 2;
				cout << win << " has won the game!" << endl;
			}
		}
		else
			countOther = 1;
	}
	if (win == 1 || win == 2)
	{
		for (int i = 0; i<ROWS; i++)
		{
			for (int j = 0; j<COLS; j++)
			{
				cout << gameBoard[i][j] << " ";
			}
			cout << endl;
		}
	}
}

bool Game::playerMove(int pieceRow, int pieceCol, int moveRow, int moveCol)  //Make the player move. Player chooses a piece and location to move to. Piece moves if possible
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
		lastMovedPiece(moveRow, moveCol);
		setCurrentTurn(getAI());
		return true;
	}
	else if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && gameBoard[moveRow][moveCol] == aiColor)
	{
		capture(pieceRow, pieceCol, moveRow, moveCol);
		lastMovedPiece(moveRow, moveCol);
		setCurrentTurn(getAI());
		return true;
	}
	else
	{
		cout << "Not possible! Make another move. \n";
		return false;
	}
}

void Game::movePiece(int board[ROWS][COLS], int pieceRow, int pieceCol, int moveRow, int moveCol) //Moves a piece on a passed in board
{
	if (board[pieceRow][pieceCol] == aiColor
		&& !ifBlocked(pieceRow, pieceCol, moveRow, moveCol)
		&& checkMove(pieceRow, pieceCol, moveRow, moveCol)
		&& board[moveRow][moveCol] == 0)
	{
		board[moveRow][moveCol] = board[pieceRow][pieceCol];
		board[pieceRow][pieceCol] = 0;
		lastMovedPiece(moveRow, moveCol);
		setCurrentTurn(getAI());
	}
	else if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && board[moveRow][moveCol] == aiColor)
	{
		checkCapture(board, pieceRow, pieceCol, moveRow, moveCol);
		lastMovedPiece(moveRow, moveCol);
		setCurrentTurn(getAI());
	}
}

 bool Game::ifBlocked(int pieceRow, int pieceCol, int moveRow, int moveCol)  //Checks if a piece is blocked when attempting to make move. Cannot jump over the enemy piece
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
		{
			--blackPieces;
		}
		else
		{
			--whitePieces;
		} 
	}
}

void Game::checkCapture(int board[ROWS][COLS], int pieceRow, int pieceCol, int moveRow, int moveCol) //Captures an enemy piece
{
	if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && board[moveRow][moveCol] != board[pieceRow][pieceCol] && board[moveRow][moveCol] != 0)
	{
		int i = board[moveRow][moveCol];
		board[moveRow][moveCol] = board[pieceRow][pieceCol];
		board[pieceRow][pieceCol] = 0;
	}
}


void Game::aiMove()  //AI's turn. Calculates all possible moves and chooses best one
{
	calculateAllMoves();
	int pieceRow;
	int pieceCol;
	int moveRow;
	int moveCol;
	pair<pair<int, int>, pair<int, int>> moveToMake = alphaBeta();
	pieceRow = moveToMake.first.first;
	pieceCol = moveToMake.first.second;
	moveRow = moveToMake.second.first;
	moveCol = moveToMake.second.second;
	bool aiMoved = false;
	while (!aiMoved)
	{
		if (gameBoard[pieceRow][pieceCol] == aiColor
			&& !ifBlocked(pieceRow, pieceCol, moveRow, moveCol)
			&& checkMove(pieceRow, pieceCol, moveRow, moveCol)
			&& gameBoard[moveRow][moveCol] == 0)
		{
			gameBoard[moveRow][moveCol] = gameBoard[pieceRow][pieceCol];
			gameBoard[pieceRow][pieceCol] = 0;
			lastMovedPiece(moveRow, moveCol);
			setCurrentTurn(getAI());
			aiMoved = true;
		}
		else if (checkMove(pieceRow, pieceCol, moveRow, moveCol) && gameBoard[moveRow][moveCol] == playerColor)
		{
			capture(pieceRow, pieceCol, moveRow, moveCol);
			lastMovedPiece(moveRow, moveCol);
			setCurrentTurn(getAI());
			aiMoved = true;
		}
	}
}
vector<pair<pair<int, int>, pair<int, int>>> Game::calculateAllMoves()  //Calculates all possible moves based on board and returns a vector of pairs of pairs
{
	vector<pair<int,int>> allPieces;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (gameBoard[i][j] == aiColor)
				allPieces.push_back(make_pair(i, j));
		}
	}	
	vector<pair<pair<int, int>, pair<int, int>>> allMoves;
	for( vector<pair<int,int>>::iterator boardIt = allPieces.begin(); boardIt != allPieces.end(); ++boardIt)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				int tempX = boardIt->first;
				int tempY = boardIt->second;
				if(checkMove(tempX, tempY, i, j) && !ifBlocked(tempX, tempY, i,j) && gameBoard[i][j] != aiColor)
				{
					pair<pair<int, int>, pair<int, int>> move = make_pair(make_pair(tempX, tempY), make_pair(i, j));
					allMoves.push_back(move);
				}
			}
		}
	}
	return allMoves;
}

vector<pair<pair<int, int>, pair<int, int>>> Game::calculateAllMovesPlayer()  //Calculates all possible moves based on board and returns a vector of pairs of pairs
{
	vector<pair<int, int>> allPieces;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (gameBoard[i][j] == playerColor)
				allPieces.push_back(make_pair(i, j));
		}
	}
	vector<pair<pair<int, int>, pair<int, int>>> allMoves;
	for (vector<pair<int, int>>::iterator boardIt = allPieces.begin(); boardIt != allPieces.end(); ++boardIt)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				int tempX = boardIt->first;
				int tempY = boardIt->second;
				if (checkMove(tempX, tempY, i, j) && !ifBlocked(tempX, tempY, i, j) && gameBoard[i][j] != playerColor)
				{
					pair<pair<int, int>, pair<int, int>> move = make_pair(make_pair(tempX, tempY), make_pair(i, j));
					allMoves.push_back(move);
				}
			}
		}
	}
	return allMoves;
}

/*void Game::outputMoves()  //Outputs list of moves
{
	for(int i = 0; i < allMoves.size();i++)
	{
		cout << allMoves[i] << endl;
	}
	cout << allMoves.size() << endl;
}*/

void Game::lastMovedPiece(int pieceRow, int pieceCol)  //Stores the last moved piece 
{
	lastMoved = make_pair(pieceRow, pieceCol);
}

int Game::getMovesRow(int pieceCol) //Gets the number of steps possible horizontally for a piece
{
	int numMoves = 0;
	for (int i = 0; i < ROWS; i++)
	{
		if (gameBoard[i][pieceCol] != 0)
			numMoves++;
	}
	return numMoves;
}

int Game::getMovesCol(int pieceRow)  //Returns the number of steps possible vertically for a piece
{
	int numMoves = 0;
	for (int i = 0; i < COLS; i++)
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
		while (i > 0 && i <= ROWS && j > 0 && j <= COLS)
		{
			if (gameBoard[i--][j--] != 0)
				diagMoves++;
		}
		int i = pieceRow;
		int j = pieceCol;
		if (i == ROWS || j == COLS && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 0 && i < ROWS && j >= 0 && j < COLS)
		{
			if (gameBoard[++i][++j] != 0)
			{
				diagMoves++;
			}
		}
	}
	else if(pieceRow < moveRow && pieceCol > moveCol) //lower left
	{
		if(i == 0 || j == COLS && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 0 && i <= ROWS && j >= 0 && j < COLS)
		{
			if (gameBoard[i--][j++] != 0)
				diagMoves++;
		}
		int i = pieceRow;
		int j = pieceCol;
		if(i == ROWS || j == 0 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 0 && i < ROWS && j > 0 && j <= COLS)
		{
			if (gameBoard[++i][--j] != 0)
				diagMoves++;
		}
	}
	else if(pieceRow > moveRow && pieceCol < moveCol) //upper right
	{
		if (i == ROWS || j == 0 && gameBoard[i][j] != 0)
		{
			diagMoves++;
		}
		while (i > 0 && i < ROWS && j > 0 && j <= COLS)
		{
			if (gameBoard[i++][j--] != 0)
			{
				diagMoves++;
			}
		}
		int i = pieceRow;
		int j = pieceCol;
		if(i == 0 || j == COLS && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 1 && i <= ROWS && j >= 0 && j < COLS)
		{
			if (gameBoard[--i][++j] != 0)
			{
					diagMoves++;
			}
		}
	}
	else if(pieceRow > moveRow && pieceCol > moveCol) //upper left
	{
		if(i == ROWS || j == COLS && gameBoard[i][j] != 0)
			diagMoves++;
		while (i >= 0 && i < ROWS && j >= 0 && j < COLS)
		{
			if (gameBoard[++i][++j] != 0)
				diagMoves++;
		}
		int i = pieceRow;
		int j = pieceCol;
		if(i == 0 || j == 0 && gameBoard[i][j] != 0)
			diagMoves++;
		while (i > 0 && i <= ROWS && j > 0 && j <= COLS)
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
	for (int k = 0; k < COLS; k++)
	{
		if (k > 0)
			cout << " " << k;
		else
			cout << "  " << k;
	}
	cout << "\n";
	for (int i = 0; i<ROWS; i++)
	{
		cout << i << " ";
		for (int j = 0; j<COLS; j++)
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