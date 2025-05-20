#include "boost/math/tools/roots.hpp"
#include "rtobject.h"
#include <cmath>

Sphere::Sphere(Coordinates pos, float radius)
    : Object(pos, Color::random()), radius(radius) {}

Sphere::Sphere(Coordinates pos, float radius, Color col)
    : Object(pos, col), radius(radius) {}

Sphere::~Sphere() {}

void Sphere::setRadius(float radius) {
    if (abs(radius) >= 0)
        ;
    this->radius = abs(radius);
}

float Sphere::getRadius() const {
    return this->radius;
}

Intersection Sphere::intersect(const Ray &ray) const {
    Intersection ret = Intersection{this};

    Coordinates movedOrigin = ray.getOrigin() - this->getOrigin();
    double a = ray.getVector() *
               ray.getVector(); // Should  == 1 be ray vector normalised
    double b = (movedOrigin * ray.getVector()) * 2.0;
    double c = movedOrigin * movedOrigin - this->radius * this->radius;
    try {
        auto [x0, x1] = boost::math::tools::quadratic_roots(a, b, c);

        // check which is shorter
        if (x0 > 0 && (x1 <= 0 || x0 <= x1)) {
            return Intersection{this, x0,
                                ray.getOrigin() + ray.getVector() * x0};
        } else if (x1 > 0 && (x0 <= 0 || x1 <= x0)) {
            return Intersection{this, x1,
                                ray.getOrigin() + ray.getVector() * x1};
        }
    } catch (const std::domain_error &) {
        // no solution
        return Intersection{};
    }
    return Intersection{};
}