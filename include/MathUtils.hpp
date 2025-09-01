#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP

#include "SDL2/SDL.h"
#include <cmath>
#include <vector>

// ========================
// Vector2 Implementation
// ========================
struct Vector2 {
    float x;
    float y;

    // Constructors
    Vector2();
    Vector2(float x_in, float y_in);
    Vector2(const Vector2 &in);

    // Operators
    float norm() const;
    float norm_squared() const;
    void normalize();
    Vector2 normalized() const;
    float dot(const Vector2 &v) const;
    void operator=(const Vector2 &v);
    void operator-();
    void operator+=(const Vector2 &v);
    Vector2 operator+(const Vector2 &v);
    void operator-=(const Vector2 &v);
    Vector2 operator-(const Vector2 &v);
    void operator*=(float s);
    Vector2 operator*(float s) const;
    bool operator==(const Vector2 &v) const;
    bool operator!=(const Vector2 &v) const;

};

// ========================
// Edge Implementation
// ========================
struct Edge {
    Vector2 p1;
    Vector2 p2;

    bool operator==(const Edge& other) const;
    bool operator!=(const Edge& other) const;
};

// ========================
// Triangle Implementation
// ========================
struct Triangle {
    Vector2 a, b, c;
    Vector2 circumcenter;

    Triangle();
    Triangle(Vector2 a_in, Vector2 b_in, Vector2 c_in);

    bool operator==(const Triangle& other) const;
    bool operator!=(const Triangle& other) const;

    bool containsVertex(const Vector2 &v) const;
    bool containsInCircumcircle(const Vector2 &p) const;
    float orientation();
    void enforceCCW();

    void computeCircumcenter();

    std::vector<Edge> edges() const;
};

// ========================
// Voronoi Cell Implementation
// ========================
struct VoronoiCell {
    Vector2 origin;                
    std::vector<Vector2> vertices;  // The ordered list of circumcenters
    SDL_Color color;
};

#endif // MATHUTILS_HPP