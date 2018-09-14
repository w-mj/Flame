//
// Created by wmj on 18-9-13.
//

#include "Flame.h"
#define CLOCKS_PER_MS ((uint)CLOCKS_PER_SEC / 1000)

void particle_move_animate(Particle* particle, clock_t start_time, clock_t draw_time) {
    int delta = uint(draw_time - start_time) / CLOCKS_PER_MS;
    if (delta) {
        particle->rect.y = particle->rect.y - delta;
        particle->active_time = draw_time;
        if (particle->rect.y < 0)
            particle->deactivate();
    }
}

Flame::Flame(int p_cnt, int area_x, int area_y, int area_w, int area_h, int par_w, int par_h):
    particle_cnt(p_cnt), x(area_x), y(area_y), w(area_w), h(area_h),
    dis_w(0, area_w), dis_h(0, area_h), particle_list((ulong)p_cnt)
{
    std::random_device rd;
    gen = std::default_random_engine(rd());

    for (int i = 0; i < p_cnt; i++) {
        int x = area_x + dis_w(gen);
        int y = area_y + dis_h(gen);
        particle_list[i] = new Particle(x, y, par_w, par_h);
        particle_list[i] -> setColor(100, 100, 50, 0xff);
        particle_list[i] -> setMoveAnimate(particle_move_animate);
        particle_list[i] -> activate();
    }
}

void Flame::update(SDL_Renderer *renderer) {
    clock_t current_time = clock();
    for (Particle* particle: particle_list) {
        if (!particle->isActive()) {
            particle->reset(x + dis_w(gen), y + dis_h(gen));
            particle->activate();
        } else {
            particle->draw(renderer, current_time);
        }
    }
}

Flame::~Flame() {
    for (Particle* particle: particle_list)
        delete particle;
}
