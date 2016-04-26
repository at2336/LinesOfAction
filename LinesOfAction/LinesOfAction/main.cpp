#include "Game.h"
using namespace std;

int main(int argc, char *argv[])
{
	Game game;
	while (game.getWin() == 0)
	{
		game.printBoard();
		int pieceRow;
		int pieceCol;
		int moveRow;
		int moveCol;
		cout << "Please enter the row of the piece you would like to move: ";
		cin >> pieceRow;
		cout << "Please enter the col of the piece you would like to move: ";
		cin >> pieceCol;
		cout << "Please enter the row of where you would like to move: ";
		cin >> moveRow;
		cout << "Please enter the col of where you would like to move: ";
		cin >> moveCol;
		if (game.playerMove(pieceRow, pieceCol, moveRow, moveCol))
		{
			game.checkWin();
			game.aiMove();
			game.checkWin();
		}
	}
}