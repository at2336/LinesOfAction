#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

const int ROWS = 7;
const int COLS = 7;

class Game
{
public:
	Game();
	int getPlayer();
	void restart();
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
	int getMovesRow(int pieceRow);
	int getMovesCol(int pieceCol);
	bool ifBlocked(int pieceRow, int pieceCol, int moveRow, int moveCol);
	int getWin();
private:
	int aiColor;
	int playerColor;
	int whitePieces = 5;
	int blackPieces = 5;
	string currentTurn;
	int gameBoard[ROWS][COLS];
	int win = 0;
};