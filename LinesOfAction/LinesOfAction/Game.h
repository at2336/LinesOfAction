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
	void playerMove(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void aiMove();
	bool checkMove(int pieceRow, int pieceCol, int moveRow, int moveCol);
	void printBoard();
	void capture();
	int getMovesRow(int pieceRow);
	int getMovesCol(int pieceCol);
private:
	int aiColor;
	int playerColor;
	int whitePieces;
	int blackPieces;
	string currentTurn;
	int gameBoard[ROWS][COLS];
};