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
    glm::vec2 velocity;
    int age, life;
    float size;
    SDL_Texture *texture = nullptr;
};
class Flame;

struct Parameter{
    Flame* instance;
    bool quit;
};

class Flame {
public:
    Flame(int p_cnt, int area_x, int area_y, int area_w, int area_h, SDL_Renderer*);
    ~Flame();
    void update();
    void blowing();
    void stop_blowing();

    glm::vec2 wind_direction;

    friend void update_t(void*);
    Parameter thread_parameter;

private:
    int particle_cnt;
    int area_x, area_y, area_w, area_h;
    std::vector<Particle> particles;
    void init_particle(Particle& p);
    void update_particle(Particle& p);
    SDL_Texture *basic_pattern_texture;
    SDL_Surface *basic_pattern_surface;
    SDL_Renderer *renderer;
    bool windy = false;

    SDL_Thread* update_thread;
};



#endif //FLAME_FLAME_H
