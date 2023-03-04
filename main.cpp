#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "./render_window.h"
#include "./entity.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
	std::cout << "INIT::ERROR: " << SDL_GetError() << std::endl;
	return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
	std::cout << "IMAGE::ERROR: " << SDL_GetError() << std::endl;
	return -1;
    }

    RenderWindow window("WINDOW", 680, 680);
    SDL_Texture* lulu = window.loadTexture("./tex/splash.png");

    Entity platform0(500, 500, lulu);
    
    bool running = true;
    SDL_Event e;
    while (running) {
	while (SDL_PollEvent(&e)) {
	    if (e.type == SDL_QUIT)
		running = false;
	}
	window.clear();
	window.render(platform0);
	window.display();
    }
    
    window.clean();
    SDL_Quit();

    return 0;
}
