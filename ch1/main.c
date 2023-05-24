#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(void) {
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else {
		/* create window */
		window = SDL_CreateWindow("SDL Tutorial",
								  SDL_WINDOWPOS_UNDEFINED,
								  SDL_WINDOWPOS_UNDEFINED,
								  SCREEN_WIDTH,
								  SCREEN_HEIGHT,
								  SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Windowcould not be created! SDL Error: %s\n", SDL_GetError());
		}
		else {
			/* get window surface */
			screenSurface = SDL_GetWindowSurface(window);

			/* fill surface white */
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			/* update the surface */
			SDL_UpdateWindowSurface(window);

			/* hack to get window to stay up */
			SDL_Event e;
			bool quit = false;

			while (quit == false) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT)
						quit = true;
				}
			}
		}
	}

	/* destroy window */
	SDL_DestroyWindow(window);

	/* quit sdl subsystems */
	SDL_Quit();

	return 0;
}
