#include "./render.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "SDL init error: " << SDL_GetError() << std::endl;

    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "IMG init error: " << SDL_GetError() << std::endl;

    window = SDL_CreateWindow(title, 0, 0, width, height, 0);
    if (window == NULL)
        std::cout << "Window error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        std::cout << "Renderer error: " << SDL_GetError() << std::endl;
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
