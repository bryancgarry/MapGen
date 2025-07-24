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
Triangle::Triangle(Vector2 a_in, Vector2 b_in, Vector2 c_in) : a{a_in}, b{b_in}, c{c_in} { enforceCCW(); }

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

std::vector<Edge> Triangle::edges() const {
    return { {a, b}, {b, c}, {c, a} };
}