#ifndef _PONG_H_
#define _PONG_H_

#include <SDL2/SDL.h>

class Pong
{
public:
    Pong();
    ~Pong() = default;

    void game_loop();
    void update(double delta_time);
    void draw();

private:
    SDL_Window * m_game_window;
    SDL_Renderer * m_game_window_renderer;
    SDL_Event m_game_window_event;
};

#endif // _PONG_H_
