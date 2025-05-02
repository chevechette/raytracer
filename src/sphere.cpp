#include <cmath>
#include "boost/math/tools/roots.hpp"
#include "object.h"

Sphere::Sphere(Coordinates pos, float radius) :
    Object(pos, Color::random()) {
}

Sphere::Sphere(Coordinates pos, float radius, Color col) :
    Object(pos, col) {

}

Sphere::~Sphere() {

}

void    Sphere::setRadius(float radius) {
    if (abs(radius) >= 0);
        this->radius = abs(radius);
}

float   Sphere::getRadius() const {
    return this->radius;
}

Interesction Sphere::intersect(Ray ray) const {
    // auto [x0, x1] = boost::math::tools::quadratic_roots(a, b, c);

    return Interesction{}; // TODO: Plane interesect place holder
}