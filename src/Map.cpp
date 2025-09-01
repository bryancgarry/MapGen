#include "Map.hpp"
#include "Delaunay.hpp"

#include <iostream>

Map::Map(int gridSize, int windowWidth, int windowHeight) : 
m_gridSize(gridSize), 
m_windowWidth(windowWidth), 
m_windowHeight(windowHeight), 
m_jitter(0.4f) 
{
    init();
}

void Map::init() {
    generateGridPoints(m_gridSize, m_jitter);
    generateTriangles();
    generateVoronoiCells();
}

void Map::render(SDL_Renderer* renderer) {
    //drawDelaunayTriangles(renderer);
    drawVoronoiCells(renderer);
    drawSeedPoints(renderer);
}

void Map::drawSeedPoints(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);   // YELLOW

    for (const auto& point : m_points) {
        //SDL_RenderDrawPoint(renderer, point.x, point.y);
        SDL_Rect pointRect = {
            static_cast<int>(point.x) - 2,
            static_cast<int>(point.y) - 2,
            4, 4
        };
        SDL_RenderFillRect(renderer, &pointRect);
    }
}

void Map::drawDelaunayTriangles(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);   // GRAY

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

void Map::drawVoronoiCells(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // GREEN

    int color = 255;

    // Iterate over voronoi cells
    for (int i = 0; i < m_voronoiCells.size(); i++) {
        // // Iterate over vertices for each cell
        // std::vector<Vector2> verts = m_voronoiCells[i].vertices;
        // for (int j = 0; j < verts.size(); j++) {
        //     Vector2 p0 = verts[j];
        //     Vector2 p1 = verts[(j + 1) % verts.size()];
        //     SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
        // }

        // VoronoiCell vc = m_voronoiCells[i];
        // int n = vc.vertices.size();
        // if (n < 3) return; // Can't draw a polygon with fewer than 3 points

        // std::vector<Sint16> vx(n);
        // std::vector<Sint16> vy(n);

        // for (int j = 0; j < n; ++j) {
        //     vx[j] = static_cast<Sint16>(vc.vertices[j].x);
        //     vy[j] = static_cast<Sint16>(vc.vertices[j].y);
        // }

        // filledPolygonRGBA(renderer, vx.data(), vy.data(), n, color, color, color, 255);

        // Iterate over vertices for each cell
        std::vector<Vector2> verts = m_voronoiCells[i].vertices;
        for (int j = 0; j < verts.size(); j++) {
            Vector2 p0 = verts[j];
            Vector2 p1 = verts[(j + 1) % verts.size()];
            SDL_RenderDrawLine(renderer, p0.x, p0.y, p1.x, p1.y);
        }

        // color += 10;
        // if (color >= 255) {
        //     color = 0;
        // }
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

    std::cout << "Point Total: " << m_points.size() << std::endl;
}

void Map::generateTriangles() {
    Delaunay del(m_points);
    m_triangles = del.getTriangles();

    std::cout << "DTri Total: " << m_triangles.size() << std::endl;
}

void Map::generateVoronoiCells() {
    for (const Vector2& point : m_points) {
        std::vector<Vector2> vertices;

        // 1. Find circumcenters of triangles that include this point
        for (const Triangle& tri : m_triangles) {
            if (tri.containsVertex(point)) {
                vertices.push_back(tri.circumcenter);
            }
        }

        // 2. Sort the circumcenters counter-clockwise around the point
        std::sort(vertices.begin(), vertices.end(), [&point](const Vector2& a, const Vector2& b) {
            float angleA = std::atan2(a.y - point.y, a.x - point.x);
            float angleB = std::atan2(b.y - point.y, b.x - point.x);
            return angleA < angleB;
        });

        // 3. Store the Voronoi vertices
        if (vertices.size() > 3) {
            VoronoiCell vc;
            vc.origin = point;
            vc.vertices = vertices;
            m_voronoiCells.push_back(vc);
        }
    }

    std::cout << "VCell Total: " << m_voronoiCells.size() << std::endl;
}

// // Sample Perlin noise at coordinates x, y
// float Map::perlin(float x, float y) {
//     // Determine grid cell corner coordinates
//     int x0 = (int)x;
//     int y0 - (int)y;
//     int x1 = x0 + 1;
//     int y1 = y0 + 1;

//     // Interpolation weights
//     float sx = x - (float)x0;
//     float sy = y - (float)y0;

// }

// Vector2 Map::randomGradient(int ix, int iy) {
//     // No precomputed gradients mean this works for any number of grid coordinates
//     const unsigned w = 8 * sizeof(unsigned);
//     const unsigned s = w / 2; 
//     unsigned a = ix, b = iy;
//     a *= 3284157443;
 
//     b ^= a << s | a >> w - s;
//     b *= 1911520717;
 
//     a ^= b << s | b >> w - s;
//     a *= 2048419325;
//     float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    
//     // Create the vector from the angle
//     Vector2 v;
//     v.x = sin(random);
//     v.y = cos(random);
 
//     return v;
// }

// // Computes the dot product of the distance and gradient vectors
// float Map::dotGridGradient(int ix, int iy, float x, float y) {
//     // Get gradient from integer coordinates
//     Vector2 gradient = randomGradient(ix, iy);

//     // Compute distance vector
//     float dx = x - (float)ix;
//     float dy = y - (float)iy;

//     // Compute the dot product
//     return (dx * gradient.x + dy * gradient.y);
// }