//
// Created by wmj on 18-9-13.
//

#ifndef FLAME_PARTICLE_H
#define FLAME_PARTICLE_H
#include <SDL2/SDL.h>

class Particle {
public:
    Particle(int x, int y, int w, int h);
    void draw(SDL_Renderer* ren, clock_t draw_time);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void reset(int x, int y);
    void activate();
    void deactivate();
    void setMoveAnimate(void (*func)(Particle*, clock_t, clock_t));
    void setColorAnimate(void (*func)(Particle*, clock_t, clock_t));
    bool isActive();

    SDL_Rect rect;
    Uint8 r, g, b, a;

private:
    clock_t active_time;
    bool is_active = false;
    void (*move_animate)(Particle*, clock_t, clock_t) = nullptr;
    void (*color_animate)(Particle*, clock_t, clock_t) = nullptr;
};


#endif //FLAME_PARTICLE_H
