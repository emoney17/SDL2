#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./pong.h"

int main()
{
    Pong pong;
    pong.game_loop();
}
