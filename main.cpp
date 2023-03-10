#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const char* title = "window";
const int width = 680;
const int height = 400;

void createWindowAndRenderer(SDL_Renderer** renderer, SDL_Window** window);
void clean(SDL_Renderer* renderer, SDL_Window* window);

int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL init error: " << SDL_GetError() << std::endl;

    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG init error: " << SDL_GetError() << std::endl;

    createWindowAndRenderer(&renderer, &window);

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    clean(renderer, window);
    return 0;
}

void createWindowAndRenderer(SDL_Renderer** renderer, SDL_Window** window)
{
    *window = SDL_CreateWindow(title, 0, 0, width, height, 0);
    if (*window == NULL)
        std::cout << "Window error: " << SDL_GetError() << std::endl;
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
        std::cout << "Renderer error: " << SDL_GetError() << std::endl;

}

void clean(SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
