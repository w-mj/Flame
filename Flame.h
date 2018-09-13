//
// Created by wmj on 18-9-13.
//

#ifndef FLAME_FLAME_H
#define FLAME_FLAME_H

#include "Particle.h"
#include <SDL2/SDL.h>
#include <vector>
#include <random>
#include <ctime>

class Flame {
public:
    Flame(int p_cnt, int area_x, int area_y, int area_w, int area_h, int par_w, int par_h);
    ~Flame();
    void update(SDL_Renderer* renderer);
private:
    int particle_cnt;
    int x, y, w, h;
    std::uniform_int_distribution<int> dis_w;
    std::uniform_int_distribution<int> dis_h;
    std::default_random_engine gen;
    std::vector<Particle*> particle_list;
};


#endif //FLAME_FLAME_H
