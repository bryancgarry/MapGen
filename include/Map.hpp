#ifndef MAP_HPP
#define MAP_HPP

#include "MathUtils.hpp"

#include <SDL2/SDL.h>
#include <vector>
#include <random>

class Map {
public:
    Map(int gridSize);
    Map(int gridSize, int windowWidth, int windowHeight);

    void render(SDL_Renderer* renderer);
    void drawSeedPoints(SDL_Renderer* renderer);
    void drawDelaunayTriangles(SDL_Renderer* renderer);

    void updateWindowSize(int width, int height);

    void generateGridPoints(int gridSize, float jitter);
    void generateTriangles();

private:
    int m_gridSize;
    float m_jitter;
    std::vector<Vector2> m_points;
    std::vector<Triangle> m_triangles;

    int m_windowWidth;
    int m_windowHeight;
};

#endif // MAP_HPP