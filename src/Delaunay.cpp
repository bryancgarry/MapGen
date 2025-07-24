#include "Delaunay.hpp"

// ========================
// Delaunay Implementation
// ========================
Delaunay::Delaunay(std::vector<Vector2> points)
{
    m_triangles = delaunayTriangulation(points);
}

std::vector<Triangle> Delaunay::delaunayTriangulation(std::vector<Vector2> points) {
    std::vector<Triangle> triangles;

    // Step 1: Create super triangle
    float minX = points[0].x, maxX = points[0].x;
    float minY = points[0].y, maxY = points[0].y;
    for (const Vector2& p : points) {
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }

    float dx = maxX - minX;
    float dy = maxY - minY;
    float deltaMax = std::max(dx, dy);
    float midx = (minX + maxX) / 2.0f;
    float midy = (minY + maxY) / 2.0f;

    Vector2 p1(midx - 20 * deltaMax, midy - deltaMax);
    Vector2 p2(midx, midy + 20 * deltaMax);
    Vector2 p3(midx + 20 * deltaMax, midy - deltaMax);

    Triangle st(p1, p2, p3);
    triangles.push_back(st);

    // Step 2: Add each point
    for (const Vector2& point : points) {
        std::vector<Triangle> badTriangles;
        std::vector<Edge> polygon;

        // Find all triangles whose circumcircle contains the point
        for (const Triangle& tri : triangles) {
            if (tri.containsInCircumcircle(point)) {
                badTriangles.push_back(tri);
            }
        }

        // Find the boundary of the cavity (unique edges)
        for (const Triangle& tri : badTriangles) {
            std::vector<Edge> edges = {
                {tri.a, tri.b}, {tri.b, tri.c}, {tri.c, tri.a}
            };

            for (const Edge& e : edges) {
                bool isShared = false;
                for (const Triangle& other : badTriangles) {
                    if (tri == other) continue;

                    std::vector<Edge> otherEdges = {
                        {other.a, other.b}, {other.b, other.c}, {other.c, other.a}
                    };

                    for (const Edge& oe : otherEdges) {
                        if (e == oe) {
                            isShared = true;
                            break;
                        }
                    }
                    if (isShared) break;
                }
                if (!isShared) polygon.push_back(e);
            }
        }

        // Remove bad triangles
        for (const Triangle& tri : badTriangles) {
            auto it = std::find(triangles.begin(), triangles.end(), tri);
            if (it != triangles.end()) {
                triangles.erase(it);
            }
        }

        // Retriangulate the cavity
        for (const Edge& e : polygon) {
            triangles.push_back({e.p1, e.p2, point});
        }
    }

    // Step 3: Remove triangles that include a super triangle vertex
    triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
        [&](const Triangle& tri) {
            return tri.containsVertex(p1) ||
                   tri.containsVertex(p2) ||
                   tri.containsVertex(p3);
        }), triangles.end());

    return triangles;
}

const std::vector<Triangle>& Delaunay::getTriangles() const {
    return m_triangles;
}