#include <iostream>
#include "Game/game.h"

Game *game = nullptr;

int main(int argc, const char *argv[])
{

	game = new Game();

	game->init("PONGGG", 1200, 800);
	game->setup();
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}
