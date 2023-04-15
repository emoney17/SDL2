#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include <SDL2/SDL.h>

class Game
{
public:
	// Game();
	// ~Game();

	bool init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();

	void setRunning (bool s)
	{
		running = s;
	}

	bool getRunning ()
	{
		return running;
	}

private:
	SDL_Window * window;
	SDL_Renderer * renderer;

	bool running;
};

#endif // _GAME_H_
