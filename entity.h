#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./entity.h"

class Entity
{
private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
public:
    Entity(float ax, float ay, SDL_Texture* atex);
    float getX(); // Getter
    float getY(); // Getter
    SDL_Texture* getTex(); // Getter
    SDL_Rect getCurrentFrame(); // Getter
};

#endif // ENTITY_H
