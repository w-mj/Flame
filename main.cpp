#include <SDL2/SDL.h>
#include <iostream>
#include "Flame.h"

using namespace std;
int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        cout << SDL_GetError() << endl;
    }
    SDL_Window *window = SDL_CreateWindow("Flame", 100, 100, 1024, 768, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Flame flame(300, 500, 350, 70, 140);

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            cout << "Quit Event";
            quit = true;
        } else {
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(renderer);
            //cout << "start update";
            flame.update(renderer);
            //cout << "......update finish" << endl;
            // SDL_SetRenderTarget(renderer, nullptr);
            // SDL_RenderCopy(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
    }
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}