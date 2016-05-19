//Runs the Game class and allows the player to play against an AI

#include "Game.h"
using namespace std;

int main(int argc, char *argv[])
{
	Game game;
	cout << "0 is an empty tile" << endl;
	cout << "1 is white piece" << endl;
	cout << "2 is black piece" << endl;
	cout << endl;
	int pieceRow = 0;
	int pieceCol = 0;
	int moveRow = 0;
	int moveCol = 0;
	while (game.getWin() == 0)
	{
		game.printBoard();
		if(game.getCurrentTurn() == game.getPlayer())
		{
			game.setCurrentTurn(game.getPlayer());
			game.playerMove(pieceRow, pieceCol, moveRow, moveCol);
			game.checkWin();
		}
		else if(game.getCurrentTurn() == game.getAI())
		{
			game.setCurrentTurn(game.getAI());
			game.aiMove();
			game.checkWin();
			game.setCurrentTurn(game.getPlayer());
		}
	}

}