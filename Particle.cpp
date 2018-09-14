//
// Created by wmj on 18-9-13.
//

#include <ctime>
#include <iostream>
#include "Particle.h"

Particle::Particle(int x, int y, int w, int h): rect {x, y, w, h} {
    r = 230;
    g = 138;
    b = 0;
}

void Particle::draw(SDL_Renderer *ren, clock_t draw_time) {
    if (!is_active)
        return;
    if(move_animate) move_animate(this, active_time, draw_time);
    if(color_animate) color_animate(this, active_time, draw_time);
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    SDL_RenderFillRect(ren, &rect);
}

void Particle::reset(int x, int y) {
    rect.x = x;
    rect.y = y;
}

void Particle::activate() {
    is_active = true;
    active_time = clock();
}

void Particle::deactivate() {
    is_active = false;
}

void Particle::setMoveAnimate(void (*func)(Particle *, clock_t, clock_t)) {
    move_animate = func;
}

void Particle::setColorAnimate(void (*func)(Particle *, clock_t, clock_t)) {
    color_animate = func;
}

void Particle::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

bool Particle::isActive() {
    return is_active;
}
