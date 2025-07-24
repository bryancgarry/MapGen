#ifndef MAP_HPP
#define MAP_HPP

#include "MathUtils.hpp"

#include <SDL2/SDL.h>
#include <vector>
#include <random>

class Map {
public:
    Map(int gridSize);

    void render(SDL_Renderer* renderer, int windowWidth, int windowHeight);

    void generateGridPoints(int gridSize, float jitter);

private:
    int m_gridSize;
    float m_jitter;
    std::vector<Vector2> points;
};

#endif // MAP_HPP