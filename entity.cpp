#include "./entity.h"

Entity::Entity(float ax, float ay, SDL_Texture* atex)
{
    x = ax;
    y = ay;
    tex = atex;

    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 400;
    currentFrame.h = 400;
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

SDL_Texture* Entity::getTex()
{
    return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}
