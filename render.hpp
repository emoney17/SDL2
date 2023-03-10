#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow
{
    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    public:
    RenderWindow(const char* title, int width, int height);
    void clear();
    void display();
    void clean();
};
