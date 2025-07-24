#ifndef DELAUNAY_HPP
#define DELAUNAY_HPP

#include "MathUtils.hpp"
#include <cmath>
#include <algorithm>
#include <vector>

#include <iostream>

class Delaunay {
public:
    Delaunay(std::vector<Vector2> points);

    Vector2 circumcenter(const Triangle& tri);
    std::vector<Triangle> delaunayTriangulation(std::vector<Vector2> points);
    const std::vector<Triangle>& getTriangles() const;

private:
    std::vector<Triangle> m_triangles;

};

#endif // DELAUNAY_HPP