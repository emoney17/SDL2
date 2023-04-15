#include "./game.hpp"

bool Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	// attempt initialize
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}
		std::cout << "SDL init success\n" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window != 0)
		{
			std::cout << "Window creation success\n" << std::endl;
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0)
			{
				std::cout << "Renderer creation success\n" << std::endl;
				SDL_SetRenderDrawColor(renderer, 225, 225, 225, 225);
			}
			else
			{
				std::cout << "Renderer init fail\n" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Window init fail\n" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n" << std::endl;
		return false;
	}

	std::cout << "Init success\n" << std::endl;
	running = true; // everything inited successfully
	return true; // start main loop
}

void Game::render()
{
	SDL_RenderClear(renderer); // clear the renderer to draw collor
	SDL_RenderPresent(renderer); // draw to screen
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	std::cout << "Cleaning game\n" << std::endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
