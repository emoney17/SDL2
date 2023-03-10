#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./render.hpp"

int main()
{
    RenderWindow window("window", 680, 400);

    SDL_Event e;
    bool running = true;
    while (running) {
        window.clear();
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
            }
        }
        window.display();
    }
    window.clean();
    return 0;
}
