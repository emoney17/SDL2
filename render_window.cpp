#include "./render_window.h"
#include "./entity.h"

RenderWindow::RenderWindow(const char* title, int width, int height)
{
    window = SDL_CreateWindow(title, 0, 0, width, height, 0);
    if (window == NULL)
	std::cout << "WINDOW::ERROR: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
	std::cout << "RENDERER::ERROR: " << SDL_GetError() << std::endl;
}

SDL_Texture* RenderWindow::loadTexture(const char *path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, path);

    if (texture == NULL)
	std::cout << "TEXTURE::ERROR: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity)
{
    // The actual size of the texture
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w; // The actual size
    src.h = entity.getCurrentFrame().h; // The actual size

    // The destination of the texture
    SDL_Rect dst;
    dst.x = entity.getX();
    dst.y = entity.getY();
    dst.w = entity.getCurrentFrame().w / 2; // Scale size
    dst.h = entity.getCurrentFrame().h / 2; // Scale size
    
    SDL_RenderCopy(renderer, entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::clean()
{
    SDL_DestroyWindow(window); 
}
