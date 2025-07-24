#include "Map.hpp"
#include "Delaunay.hpp"

#include <iostream>

Map::Map(int gridSize) : 
m_gridSize(gridSize), 
m_jitter(0.4f) 
{
    generateGridPoints(m_gridSize, m_jitter);
    generateTriangles();
}

Map::Map(int gridSize, int windowWidth, int windowHeight) : 
m_gridSize(gridSize), 
m_windowWidth(windowWidth), 
m_windowHeight(windowHeight), 
m_jitter(0.5f) 
{
    generateGridPoints(m_gridSize, m_jitter);
    generateTriangles();
}

void Map::render(SDL_Renderer* renderer) {
    drawDelaunayTriangles(renderer);
    drawSeedPoints(renderer);
}

void Map::drawSeedPoints(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // RED

    for (const auto& point : m_points) {
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }
}

void Map::drawDelaunayTriangles(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);   // GRAY

    // Iterate over triangles
    for (int i = 0; i < m_triangles.size(); i++) {
        Vector2 p0 = m_triangles[i].a;
        Vector2 p1 = m_triangles[i].b;
        Vector2 p2 = m_triangles[i].c;

        SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
        SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
        SDL_RenderDrawLine(renderer, p2.x, p2.y, p0.x, p0.y);
    }
}

void Map::updateWindowSize(int width, int height) {
    m_windowWidth = width;
    m_windowHeight = height;
}

void Map::generateGridPoints(int gridSize, float jitter) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Mimics Math.random()

    float spacingX = static_cast<float>(m_windowWidth) / m_gridSize;
    float spacingY = static_cast<float>(m_windowHeight) / m_gridSize;

    for (int x = 0; x <= gridSize; x++) {
        for (int y = 0; y <= gridSize; y++) {
            // Only apply jitter if not on the edge
            float jitterX = 0.0f;
            float jitterY = 0.0f;
            if ((x > 0 && x < gridSize) && (y > 0 && y < gridSize)) {
                jitterX = jitter * (dist(rng) - dist(rng));
                jitterY = jitter * (dist(rng) - dist(rng));
            }

            // Apply jitter to coordinate
            float baseX = (float)x + jitterX;
            float baseY = (float)y + jitterY;

            // Add point to point vector
            Vector2 p;
            p.x = baseX * spacingX; 
            p.y = baseY * spacingY;
            m_points.emplace_back(p);
        }
    }
}

void Map::generateTriangles() {
    Delaunay del(m_points);
    m_triangles = del.getTriangles();
}


