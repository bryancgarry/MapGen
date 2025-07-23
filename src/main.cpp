#include <SDL2/SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int CELL_SIZE = 16;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("SDL2 Grid",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN);
    if (!win) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen with black
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // Set grid color (white)
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

        // Draw vertical grid lines
        for (int x = 0; x <= WINDOW_WIDTH; x += CELL_SIZE) {
            SDL_RenderDrawLine(ren, x, 0, x, WINDOW_HEIGHT);
        }

        // Draw horizontal grid lines
        for (int y = 0; y <= WINDOW_HEIGHT; y += CELL_SIZE) {
            SDL_RenderDrawLine(ren, 0, y, WINDOW_WIDTH, y);
        }

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

