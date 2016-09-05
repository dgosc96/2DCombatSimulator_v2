#include "gameSystem.h"

#include <conio.h>
#include <iostream>


int main() {


	gameSystem game;
	
	char winner = game.gameLoop();

	game.winner(winner);

	std::cout << "Press any key to exit...";
	_getch();
	return 0;
}