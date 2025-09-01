#ifndef MAP_HPP
#define MAP_HPP

#include "MathUtils.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <random>

class Map {
public:
    Map(int gridSize, int windowWidth, int windowHeight);

    void init();

    void render(SDL_Renderer* renderer);

    void drawSeedPoints(SDL_Renderer* renderer);
    void drawDelaunayTriangles(SDL_Renderer* renderer);
    void drawVoronoiCells(SDL_Renderer* renderer);

    void updateWindowSize(int width, int height);

    void generateGridPoints(int gridSize, float jitter);
    void generateTriangles();
    void generateVoronoiCells();

    // Perlin Noise Generation - modified from https://www.youtube.com/watch?v=kCIaHqb60Cw
    float perlin(float x, float y);
    Vector2 randomGradient(int ix, int iy);
    float dotGridGradient(int ix, int iy, float x, float y);


private:
    int m_gridSize;
    float m_jitter;
    std::vector<Vector2> m_points;
    std::vector<Triangle> m_triangles;
    std::vector<VoronoiCell> m_voronoiCells;

    int m_windowWidth;
    int m_windowHeight;
};

#endif // MAP_HPP