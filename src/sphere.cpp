#include <cmath>
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
    return Interesction{}; // TODO: Plane interesect place holder
}