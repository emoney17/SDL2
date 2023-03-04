#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./entity.h"

class RenderWindow
{
private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* path);
    void clear();
    void render(Entity& entity);
    void display();
    void clean();
};

#endif // RENDER_WINDOW_H
