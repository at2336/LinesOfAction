#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const int ROWS = 7;
const int COLS = 7;

class Game
{
public:
	Game();
	int getPlayer();
	void restart();
	int getAI();
	void setWhitePiecesNum(int num);
	void setBlackPiecesNum(int num);
	int getBlackPieces();
	int getWhitePieces();
	void checkWin();
	bool playerMove();
	void aiMove();
	bool checkMove(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void printBoard();
	void capture(int pieceRow, int pieceCol, int moveRow, int moveCol);
	int getMovesRow(int pieceRow);
	int getMovesCol(int pieceCol);
	bool ifBlocked(int pieceRow, int pieceCol, int moveRow, int moveCol);
	int getWin();
	void calculateAllMoves();
	pair<int,int> lastMovedPiece();
	void setCurrentTurn(int turn);
	int getCurrentTurn();
	void outputMoves();
	int getMovesDiag(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void lastMovedPiece(int pieceRow, int pieceCol);
private:
	int pieceRow;
	int pieceCol;
	int moveRow;
	int moveCol;
	int aiColor;
	int playerColor;
	int whitePieces;
	int blackPieces;
	int currentTurn;
	int gameBoard[ROWS][COLS];
	int win;
	int diagMoves;
	string lastMoved;
	vector<string> allMoves;
};