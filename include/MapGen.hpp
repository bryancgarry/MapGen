#ifndef MAPGEN_HPP
#define MAPGEN_HPP

#include <SDL2/SDL.h>
#include "Map.hpp"

class MapGen {
public:
    MapGen(int gridSize, int width, int height);
    ~MapGen();

    void run();

private:
    bool initSDL();
    void processEvents();
    void update();
    void render();
    void cleanup();

    SDL_Window* window;
    SDL_Renderer* renderer;
    int windowWidth;
    int windowHeight;
    bool isRunning;

    Map map;
};

#endif // MAPGEN_HPP

