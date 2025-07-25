#include "MathUtils.hpp"

// ========================
// Vector2 Implementation
// ========================
Vector2::Vector2() : x{0.0f}, y{0.0f} {}
Vector2::Vector2(float x_in, float y_in) : x{x_in}, y{y_in} {}
Vector2::Vector2(const Vector2 &in) { *this = in; }

// Magnitude
float Vector2::norm() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::norm_squared() const {
    return x * x + y * y;
}

// Normalize
void Vector2::normalize() {
    float n = norm();
    if (n != 0.0f) {
        x /= n;
        y /= n;
    }
}

Vector2 Vector2::normalized() const {
    float n = norm();
    if (n != 0.0f) {
        return Vector2(x / n, y / n);
    }
    return Vector2(0.0f, 0.0f);
}

// Dot product
float Vector2::dot(const Vector2 &v) const {
    return x * v.x + y * v.y;
}

// Operators
void Vector2::operator=(const Vector2 &v) {
    x = v.x;
    y = v.y;
}

void Vector2::operator-() {
    x = -x;
    y = -y;
}

void Vector2::operator+=(const Vector2 &v) {
    x += v.x;
    y += v.y;
}

Vector2 Vector2::operator+(const Vector2 &v) {
    return Vector2(x + v.x, y + v.y);
}

void Vector2::operator-=(const Vector2 &v) {
    x -= v.x;
    y -= v.y;
}

Vector2 Vector2::operator-(const Vector2 &v) {
    return Vector2(x - v.x, y - v.y);
}

void Vector2::operator*=(float s) {
    x *= s;
    y *= s;
}

Vector2 Vector2::operator*(float s) const {
    return Vector2(x * s, y * s);
}

bool Vector2::operator==(const Vector2 &v) const {
    return x == v.x && y == v.y;
}

bool Vector2::operator!=(const Vector2& v) const {
    return !(*this == v);
}


// ========================
// Edge Implementation
// ========================
bool Edge::operator==(const Edge& other) const {
        return (p1 == other.p1 && p2 == other.p2) ||
               (p1 == other.p2 && p2 == other.p1);
}

bool Edge::operator!=(const Edge& other) const {
    return !(*this == other);
}


// ========================
// Triangle Implementation
// ========================
Triangle::Triangle() : a{Vector2{0.0f, 0.0f}}, b{Vector2{0.0f, 0.0f}}, c{Vector2{0.0f, 0.0f}} {}
Triangle::Triangle(Vector2 a_in, Vector2 b_in, Vector2 c_in) : a{a_in}, b{b_in}, c{c_in} { 
    enforceCCW(); 
    computeCircumcenter();
}

bool Triangle::operator==(const Triangle& other) const {
        return other.containsVertex(a) &&
               other.containsVertex(b) &&
               other.containsVertex(c);
}

bool Triangle::operator!=(const Triangle& other) const {
    return !(*this == other);
}

bool Triangle::containsVertex(const Vector2& v) const {
    return a == v || b == v || c == v;
}

bool Triangle::containsInCircumcircle(const Vector2 &p) const {
    float ax = a.x - p.x;
    float ay = a.y - p.y;
    float bx = b.x - p.x;
    float by = b.y - p.y;
    float cx = c.x - p.x;
    float cy = c.y - p.y;

    float det = (ax * ax + ay * ay) * (bx * cy - cx * by)
              - (bx * bx + by * by) * (ax * cy - cx * ay)
              + (cx * cx + cy * cy) * (ax * by - bx * ay);

    return det > 0;
}

float Triangle::orientation() {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void Triangle::enforceCCW() {
    if (orientation() < 0) {
        std::swap(b, c);
    }
}

void Triangle::computeCircumcenter() {
    float d = 2 * (a.x * (b.y - c.y) +
                   b.x * (c.y - a.y) +
                   c.x * (a.y - b.y));

    if (std::abs(d) < 1e-6f) {
        // Degenerate triangle; return center of bounding box
        float minX = std::min({a.x, b.x, c.x});
        float maxX = std::max({a.x, b.x, c.x});
        float minY = std::min({a.y, b.y, c.y});
        float maxY = std::max({a.y, b.y, c.y});
        circumcenter.x = (minX + maxX) * 0.5f;
        circumcenter.y = (minY + maxY) * 0.5f;
        return;
    }

    float aSq = a.x * a.x + a.y * a.y;
    float bSq = b.x * b.x + b.y * b.y;
    float cSq = c.x * c.x + c.y * c.y;

    float ux = (aSq * (b.y - c.y) +
                bSq * (c.y - a.y) +
                cSq * (a.y - b.y)) / d;

    float uy = (aSq * (c.x - b.x) +
                bSq * (a.x - c.x) +
                cSq * (b.x - a.x)) / d;

    circumcenter.x = ux;
    circumcenter.y = uy;
}

std::vector<Edge> Triangle::edges() const {
    return { {a, b}, {b, c}, {c, a} };
}