#include <cmath>
#include "object.h"

Sphere::Sphere(Coordinates pos, float radius) :
    Object(pos, Color{0, 0, 0, 0}) {
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

Coordinates Sphere::intersect(Ray ray) const {
    return Coordinates{0, 0, 0}; // TODO: Sphere interesect place holder
}