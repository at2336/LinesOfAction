#include "Game.h"
using namespace std;

int main(int argc, char *argv[])
{
	Game game;
	cout << "0 is an empty tile" << endl;
	cout << "1 is white piece" << endl;
	cout << "2 is black piece" << endl;
	cout << endl;
	while (game.getWin() == 0)
	{
		game.printBoard();
		if(game.getCurrentTurn() == game.getPlayer())
		{
			game.setCurrentTurn(game.getPlayer());
			cout << game.getCurrentTurn();
			game.playerMove();
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