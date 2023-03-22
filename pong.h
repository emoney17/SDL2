#ifndef _PONG_H_
#define _PONG_H_

#include <SDL2/SDL.h>
#include "./paddle.h"

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
    SDL_Event m_game_window_event;
    SDL_Renderer * m_game_window_renderer;

    Paddle m_left_paddle;
    Paddle m_right_paddle;
};

#endif // _PONG_H_
