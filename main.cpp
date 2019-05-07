#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Flame.h"
#include "wood.c"

using namespace std;

template<typename T>
T limit(T a, T min, T max) {
    if (a < min) return min;
    if (a > max) return max;
    return a;
}

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cout << SDL_GetError() << endl;
    }
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("Flame", 100, 100, 1024, 768, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Color black = {0, 0, 0, 0xff};

    SDL_Surface* image_surface = SDL_CreateRGBSurfaceWithFormatFrom(
            gimp_image_wood.pixel_data, gimp_image_wood.width, gimp_image_wood.height, 32,
            gimp_image_wood.bytes_per_pixel * gimp_image_wood.width, SDL_PIXELFORMAT_RGBA32);
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_Rect wood_area = {440, 400, image_surface->w, image_surface->h / 2};

#ifdef linux
    TTF_Font *font = TTF_OpenFont("./arial.ttf", 16);
#endif
#ifdef win32
    TTF_Font *font = nullptr;
#endif
    if (font == nullptr) {
        cout << "Fail to load font";
        exit(-1);
    }

    Flame flame(400, 450, 200, 70, 200, renderer);

    SDL_Event event;
    clock_t last_frame = clock();
    char fps_text[10];
    uint cnt = 0;
    SDL_Surface *fps_surface = nullptr;
    SDL_Texture *fps_texture = nullptr;
    SDL_Rect text_area = {0, 0, 0, 0};
    while (true) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            cout << "Quit Event";
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT)
                flame.blowing();
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT)
                flame.stop_blowing();
        } else if (event.type == SDL_MOUSEMOTION) {
            double dist = sqrt(pow(event.motion.x - 485, 2) + pow(event.motion.y - 400, 2));
            double force_x = 1.5 * (485 - event.motion.x) / dist;
            double force_y = 1.5 * (400 - event.motion.y) / dist;
            flame.wind_direction = {force_x, force_y};
        }

        cnt++;
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, nullptr, &wood_area);
        flame.update();

        if (clock() - last_frame >= CLOCKS_PER_SEC) {
            if (fps_surface != nullptr) SDL_FreeSurface(fps_surface);
            if (fps_texture != nullptr) SDL_DestroyTexture(fps_texture);
            last_frame = clock();
            sprintf(fps_text, "%-5dfps", cnt);
            fps_surface = TTF_RenderText_Solid(font, fps_text, black);
            fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
            text_area = {0, 0, fps_surface->w, fps_surface->h};
            cnt = 0;
        }
        if (fps_texture != nullptr)
            SDL_RenderCopy(renderer, fps_texture, nullptr, &text_area);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    if (fps_surface != nullptr) SDL_FreeSurface(fps_surface);
    if (fps_texture != nullptr) SDL_DestroyTexture(fps_texture);
    TTF_CloseFont(font);
    SDL_FreeSurface(image_surface);
    SDL_DestroyTexture(image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}