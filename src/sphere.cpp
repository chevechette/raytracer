#include "boost/math/tools/roots.hpp"
#include "rtobject.h"
#include <cmath>

Sphere::Sphere(Coordinates pos, float radius) : Object(pos, Color::random()) {
    this->radius = radius;
}

Sphere::Sphere(Coordinates pos, float radius, Color col) : Object(pos, col) {
    this->radius = radius;
}

Sphere::~Sphere() {}

void Sphere::setRadius(float radius) {
    if (abs(radius) >= 0)
        ;
    this->radius = abs(radius);
}

float Sphere::getRadius() const {
    return this->radius;
}

#include <fmt/core.h>
#include <iostream>
Intersection Sphere::intersect(const Ray &ray) const {
    Intersection ret = Intersection{this};
    // fmt::print(stdout, "RAY ORIGIN : {} ; {} ; {}\n", ray.getOrigin().x,
    //            ray.getOrigin().y, ray.getOrigin().z);
    // fmt::print(stdout, "RAY DIRECTION : {} ; {} ; {}\n", ray.getVector().x,
    //            ray.getVector().y, ray.getVector().z);
    // fmt::print(stdout, "AIMING AT : {} ; {} ; {}; {}\n", this->origin.x,
    //            this->origin.y, this->origin.z, this->radius);

    Coordinates movedOrigin = ray.getOrigin() - this->getOrigin();
    double a = ray.getVector() *
               ray.getVector(); // Should  == 1 be ray vector normalised 
    double b = (movedOrigin * ray.getVector()) * 2.0;
    double c = movedOrigin * movedOrigin - this->radius * this->radius;
    try {
        auto [x0, x1] = boost::math::tools::quadratic_roots(a, b, c);

        // check which is shorter
        if (x0 > 0 && x0 <= x1) {
            return Intersection{this, x0,
                                ray.getOrigin() + ray.getVector() * x0};
        } else if (x1 > 0 && x1 <= x0) {

            // std::cout << " RETURN X1 " << std::endl;
            return Intersection{this, x1,
                                ray.getOrigin() + ray.getVector() * x1};
        }
    } catch (const std::domain_error &) {
        // no solution
        return Intersection{};
    }
    return Intersection{};
}