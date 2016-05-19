//Header file for the game
//Class file for Game

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 6;
const int COLS = 6;

class Game
{
public:
	Game();
public:
	int getPlayer();
	int getAI();
	void setWhitePiecesNum(int num);
	void setBlackPiecesNum(int num);
	int getBlackPieces();
	int getWhitePieces();
	void checkWin();
	bool playerMove(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void aiMove();
	bool checkMove(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void printBoard();
	void capture(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void checkCapture(int board[ROWS][COLS], int pieceRow, int pieceCol, int moveRow, int moveCol);
	int getMovesRow(int pieceRow);
	int getMovesCol(int pieceCol);
	bool ifBlocked(int pieceRow, int pieceCol, int moveRow, int moveCol);
	int getWin();
	vector<pair<pair<int, int>, pair<int, int>>> calculateAllMoves();
	void setCurrentTurn(int turn);
	int getCurrentTurn();
	vector<pair<pair<int, int>, pair<int, int>>> calculateAllMovesPlayer();
	int getMovesDiag(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void lastMovedPiece(int pieceRow, int pieceCol);
	void movePiece(int board[ROWS][COLS], int pieceRow, int pieceCol, int moveRow, int moveCol);
	pair<pair<int, int>,pair<int,int>> alphaBeta();
	int maxVal(int tempBoard[ROWS][COLS], int alpha, int beta, int depth);
	int minVal(int tempBoard[ROWS][COLS], int alpha, int beta, int depth);
	pair<pair<int,int>,pair<int,int>> action(int minUtil, int maxUtil, int depth);
	bool checkAIWin(int tempBoard[ROWS][COLS]);
	bool checkPlayerWin(int tempBoard[ROWS][COLS]);
	int evaluate(int tempBoard[ROWS][COLS]);
private:
	clock_t timer;
	int nodes = 0;
	int depth;
	int maxDepth = 0;
	int maxEval = 0;
	int minEval = 0;
	int minPrune = 0;
	int maxPrune = 0;
	int aiColor;
	int playerColor;
	int whitePieces;
	int blackPieces;
	int currentTurn;
	int gameBoard[ROWS][COLS];
	int win;
	int diagMoves;
	pair<int,int> lastMoved;
};