#include "Map.hpp"

Map::Map(int gridSize) : m_gridSize(gridSize), m_jitter(0.5f) {
    generateGridPoints(m_gridSize, m_jitter);
}

void Map::render(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    float spacingX = static_cast<float>(windowWidth) / m_gridSize;
    float spacingY = static_cast<float>(windowHeight) / m_gridSize;

    for (const auto& point : points) {
        int px = static_cast<int>(point.x * spacingX);
        int py = static_cast<int>(point.y * spacingY);
        SDL_RenderDrawPoint(renderer, px, py);
    }
}

void Map::generateGridPoints(int gridSize, float jitter) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Mimics Math.random()

    for (int x = 0; x <= gridSize; x++) {
        for (int y = 0; y <= gridSize; y++) {
            float jitterX = jitter * (dist(rng) - dist(rng));
            float jitterY = jitter * (dist(rng) - dist(rng));
            points.emplace_back(Vector2((float)x + jitterX, (float)y + jitterY));
        }
    }
}


