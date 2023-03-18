#include "./pong.h"

// Create window and renderer in constructor
Pong::Pong() 
{
    SDL_CreateWindowAndRenderer(
	680,
	400,
	SDL_WINDOW_RESIZABLE,
	&m_game_window,
	&m_game_window_renderer);
    // Set independent resolution for when resized
    SDL_RenderSetLogicalSize(m_game_window_renderer, 400, 400);
}

void Pong::game_loop()
{
    bool running = true;
    while (running)
    {
	while (SDL_PollEvent(&m_game_window_event))
	{
	    switch (m_game_window_event.type)
	    {
	    case SDL_QUIT:
		running = false;
	    }
	}
	update(1.0/60);
	draw();
    }
}

void Pong::update(double delta_time)
{
    
}

void Pong::draw()
{
    SDL_RenderClear(m_game_window_renderer);
    SDL_RenderPresent(m_game_window_renderer);
}
