#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Flame.h"
using namespace std;

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
                       TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cout << SDL_GetError() << endl;
    }
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Flame", 100, 100, 1024, 768, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Color black = {0, 0, 0, 0xff};
#ifdef linux
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/arial.ttf", 16);
#endif
#ifdef win32
    TTF_Font *font = nullptr;
#endif
    if (font == nullptr) {
        cout << "Fail to load font";
        exit(-1);
    }

    Flame flame(500, 500, 350, 70, 200);

    SDL_Event event;
    bool quit = false;
    clock_t last_frame = clock();
    char fps_text[10];
    uint cnt = 0;
    SDL_Surface *fps_surface = nullptr;
    SDL_Texture *fps_texture = nullptr;
    SDL_Rect text_area = {0, 0, 0, 0};
    while (!quit) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            cout << "Quit Event";
            quit = true;
        } else {
            cnt++;
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(renderer);
            flame.update(renderer);
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
        }
    }
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}