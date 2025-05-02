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
    Coordinates movedOrigin = ray.getOrigin() - this->getOrigin();
    double      a = ray.getVector() * ray.getVector(); // Should  == 1 be ray vector normalised // TODO: Normalise all vectors on init;
    double      b = movedOrigin * ray.getVector() * 2.0;
    double      c = movedOrigin * movedOrigin - this->radius * this->radius;

    auto [x0, x1] = boost::math::tools::quadratic_roots(a, b, c);
    return Interesction{}; // TODO: Plane interesect place holder
}