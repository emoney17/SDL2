#include "./game.hpp"

// Game object
Game * game = 0;

int main(int argc, char *argv[])
{
	game = new Game();

	game->init("Chapter 1", 100, 100, 600, 480, false);

	while (game->getRunning())
	{
		game->handleEvents();
		game->render();
	}

	game->clean();
	return 0;
}

