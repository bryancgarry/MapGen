#include "MapGen.hpp"
#include <iostream>

MapGen::MapGen(int gridSize, int width, int height)
    : window(nullptr), renderer(nullptr),
      windowWidth(width), windowHeight(height),
      isRunning(true), map(gridSize, width, height) {}

MapGen::~MapGen() {
    cleanup();
}

bool MapGen::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    window = SDL_CreateWindow("Map Generator",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight,
                              SDL_WINDOW_RESIZABLE);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    return true;
}

void MapGen::run() {
    if (!initSDL()) return;

    while (isRunning) {
        processEvents();
        update();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}

void MapGen::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            isRunning = false;
        else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            windowWidth = event.window.data1;
            windowHeight = event.window.data2;
            map.updateWindowSize(windowWidth, windowHeight);
        }
    }
}

void MapGen::update() {
    // Nothing dynamic for now
}

void MapGen::render() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    map.render(renderer);

    SDL_RenderPresent(renderer);
}

void MapGen::cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}