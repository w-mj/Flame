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

    thread_parameter.instance = this;
    thread_parameter.quit = false;
}


glm::vec2 add(const glm::vec2& a, const glm::vec2& b) {
  return {a.x + b.x, a.y + b.y};
}

void Flame::update() {
    for (Particle& p: particles) {
        update_particle(p);
        SDL_Rect r = {static_cast<int>(p.position.x), static_cast<int>(p.position.y),
                      static_cast<int>(p.size), static_cast<int>(p.size)};
        SDL_RenderCopy(renderer, p.texture, nullptr, &r);

    }
}


void Flame::init_particle(Particle &p) {
    static int mid_x = area_x + area_w / 2;
    static std::default_random_engine gen;
    static std::normal_distribution<float> normal(mid_x, 11);
    static std::uniform_int_distribution<int> dis_h(area_y + area_h - 5, area_y + area_h);
    static std::uniform_real_distribution<float> percent(0, 1);
    static glm::vec2 max_velocity = {0, -1};
    static std::uniform_int_distribution<int> life(0, 200);

    p.position = {normal(gen), dis_h(gen)};
    p.velocity = {0, max_velocity.y * percent(gen)};
    if (windy) {
        p.velocity.x = p.velocity.x + wind_direction.x;
        p.velocity.y = p.velocity.y + wind_direction.y;
        if (p.velocity.x > 1) p.velocity.x = 1;
        if (p.velocity.y < -1) p.velocity.y = -1;
    }
    p.size = 9;
    p.life = life(gen);
    p.age = 0;
    if (p.texture != nullptr) SDL_DestroyTexture(p.texture);
    p.texture = SDL_CreateTextureFromSurface(renderer, basic_pattern_surface);
    Uint8 dist = static_cast<Uint8>(abs(p.position.x - mid_x));
    Uint8 mod = 255 - dist * 2;
    SDL_SetTextureAlphaMod(p.texture, mod);
    SDL_SetTextureColorMod(p.texture, mod, mod << 1, 20);
}


void Flame::update_particle(Particle &p) {
    p.age += 1;
    if (p.age > p.life ||
        p.position.x < 10 || p.position.x > 1000 ||
        p.position.y < area_y || p.position.y > area_y + area_h)
        init_particle(p);
    else {
        p.position = add(p.position, p.velocity);
        Uint8 radio = static_cast<Uint8>((static_cast<float>(p.life - p.age)) / p.life * 256);
        SDL_SetTextureAlphaMod(p.texture, radio);
    }
}

Flame::~Flame() {
    thread_parameter.quit = true;
    SDL_FreeSurface(basic_pattern_surface);
    SDL_DestroyTexture(basic_pattern_texture);
    for (Particle &p : particles)
        SDL_DestroyTexture(p.texture);
}

void Flame::blowing() {
    if (!windy) {
        for (Particle &p: particles) {
            p.velocity.x = p.velocity.x + wind_direction.x;
            p.velocity.y = p.velocity.y + wind_direction.y;
            if (p.velocity.x > 1) p.velocity.x = 1;
            if (p.velocity.y < -1) p.velocity.y = -1;
        }
        windy = true;
    }
}

void Flame::stop_blowing() {
    static std::default_random_engine gen;
    static std::uniform_real_distribution<float> percent(0, 1);
    for (Particle& p: particles) {
        p.velocity.x = 0;
        p.velocity.y = -percent(gen);
    }
    windy = false;
}
