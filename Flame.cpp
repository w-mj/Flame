//
// Created by wmj on 18-9-13.
//

#include <iostream>
#include <unistd.h>
#include "Flame.h"
#include "pattern.c"
#define CLOCKS_PER_MS ((uint)CLOCKS_PER_SEC / 1000)

Flame::Flame(int p_cnt, int area_x, int area_y, int area_w, int area_h, SDL_Renderer* renderer):
    particle_cnt(p_cnt), area_x(area_x), area_y(area_y), area_w(area_w), area_h(area_h),
    particles((ulong)p_cnt), renderer(renderer)
{
    basic_pattern_surface = SDL_CreateRGBSurfaceWithFormatFrom(
            gimp_image.pixel_data, gimp_image.width, gimp_image.height, 32,
            gimp_image.bytes_per_pixel * gimp_image.width, SDL_PIXELFORMAT_RGBA32);
    basic_pattern_texture = SDL_CreateTextureFromSurface(renderer, basic_pattern_surface);

    for (int x = 0; x < p_cnt; x++) {
        init_particle(particles[x]);
    }
}

glm::vec2 add(const glm::vec2& a, const glm::vec2& b) {
  return {a.x + b.x, a.y + b.y};
}

void Flame::update() {
    clock_t current_time = clock();
    static clock_t last_update_time = 0;
    if ((current_time - last_update_time) / CLOCKS_PER_MS >= 1) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0);
        for (Particle& p: particles) {
            update_particle(p);
            SDL_Rect r = {static_cast<int>(p.position.x), static_cast<int>(p.position.y),
                          static_cast<int>(p.size), static_cast<int>(p.size)};
            SDL_RenderCopy(renderer, basic_pattern_texture, nullptr, &r);
        }
    }
}


void Flame::init_particle(Particle &p) {
    static std::default_random_engine gen;
    static std::normal_distribution<float> normal(area_x + area_w / 2, 11);
    static std::uniform_int_distribution<int> dis_h(area_y + area_h - 5, area_y + area_h);
    static std::uniform_real_distribution<float> percent(0, 1);
    static glm::vec2 max_velocity = {0, -1};
    static std::uniform_int_distribution<int> life(0, 200);

    p.position = {normal(gen), dis_h(gen)};
    p.velocity = {max_velocity.x * percent(gen), max_velocity.y * percent(gen)};
    p.accelerate = {0, -0.01};
    p.alpha = 255;
    p.size = 9;
    p.life = life(gen);
    p.age = 0;
    p.alpha = 200;
}


void Flame::update_particle(Particle &p) {
    p.age += 1;
    if (p.age > p.life ||
        p.position.x < area_x || p.position.x > area_x + area_w ||
        p.position.y < area_y || p.position.y > area_y + area_h)
        init_particle(p);
    else {
        // p.velocity = add(p.velocity, p.accelerate);
        p.position = add(p.position, p.velocity);
    }
}

Flame::~Flame() {
    SDL_FreeSurface(basic_pattern_surface);
    SDL_DestroyTexture(basic_pattern_texture);
}
