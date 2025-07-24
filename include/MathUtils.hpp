#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP

#include <cmath>

// Vector2 struct
struct Vector2 {

    float x;
    float y;

    // Constructors
    Vector2();
    Vector2(float x_in, float y_in);
    Vector2(const Vector2 &in);

};

#endif // MATHUTILS_HPP