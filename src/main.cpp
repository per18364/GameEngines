#include <iostream>
#include <game.h>
#include <SDL2/SDL.h>

Game *game = nullptr;

int main(int argc, const char *argv[])
{

	game = new Game();

	game->fps = 55;

	game->init("PONGGG", 1200, 800);
	game->setup();
	while (game->running())
	{
		game->startClock = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		if ((1000 / game->fps) > SDL_GetTicks() - game->startClock)
		{
			SDL_Delay(1000 / game->fps - (SDL_GetTicks() - game->startClock));
		}

		game->prev_time = game->curr_time;
		game->curr_time = SDL_GetTicks();
		game->delta_time = game->curr_time - game->prev_time;
	}

	game->clean();

	return 0;
}
