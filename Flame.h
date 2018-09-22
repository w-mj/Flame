//
// Created by wmj on 18-9-13.
//

#ifndef FLAME_FLAME_H
#define FLAME_FLAME_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <vector>
#include <random>
#include <ctime>

struct Particle {
    glm::vec2 position;
    glm::vec2 accelerate;
    glm::vec2 velocity;
    int age, life;
    float size;
    int alpha;
};

class Flame {
public:
    Flame(int p_cnt, int area_x, int area_y, int area_w, int area_h);
    ~Flame() {}
    void update(SDL_Renderer* renderer);
private:
    int particle_cnt;
    int area_x, area_y, area_w, area_h;
    std::vector<Particle> particles;

    void init_particle(Particle& p);
    void update_particle(Particle& p);
};


#endif //FLAME_FLAME_H
