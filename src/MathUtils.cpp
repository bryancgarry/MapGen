#include "MathUtils.hpp"

// Vector 2
Vector2::Vector2() : x{0.0f}, y{0.0f} {}
Vector2::Vector2(float x_in, float y_in) : x{x_in}, y{y_in} {}
Vector2::Vector2(const Vector2 &in) { *this = in; }