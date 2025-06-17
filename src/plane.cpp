#include "rtobject.h"
#include "structs.h"

#include <cmath>
#include "logger.h"

Plane::Plane(Coordinates origin, Coordinates normal)
    : Object(origin, Color{1, 1, 1, 1}), normalVec{normal.normalize()},
      height{-1}, width{-1} {
    this->setVectors();
}

Plane::Plane(Coordinates origin, Coordinates normal, Color col)
    : Object(origin, col), normalVec{normal.normalize()}, height{-1},
      width{-1} {
    this->setVectors();
}

Plane::Plane(Coordinates origin, Coordinates normal, float height, float width)
    : Object(origin, Color{1, 1, 1, 1}), normalVec{normal.normalize()},
      height{height}, width{width} {
    this->setVectors();
}

Plane::Plane(Coordinates origin, Coordinates normal, Color col, float height,
             float width)
    : Object(origin, col), normalVec{normal.normalize()}, height{height},
      width{width} {
    this->setVectors();
}

Plane::~Plane() {
    spdlog::info("Destroyed : {}", this->to_string());
}

void Plane::setNormal(Coordinates norm) {
    this->normalVec = norm;
}

Coordinates Plane::getNormal() const {
    return this->normalVec;
}

void Plane::setVectors() {
    Coordinates vec =
        (std::abs(this->normalVec.x) < std::abs(this->normalVec.y))
            ? Coordinates{0, 1, 0}
            : Coordinates{0, 0, 1};
    this->h = this->normalVec ^ vec;
    this->w = this->normalVec ^ this->h;
}

bool Plane::checkHeight(const Coordinates &v) const {
    if (this->height <= 0)
        return true;
    return ((this->h * v) <= height);
}

bool Plane::checkWidth(const Coordinates &v) const {
    if (this->width <= 0)
        return true;
    return ((this->w * v) <= width);
}

float Plane::getHeight(float x) const {
    return this->height;
}

float Plane::getwidth(float x) const {
    return this->width;
}

Intersection Plane::intersect(const Ray &ray) const {
    double cosPlane = ray.getVector() * this->getNormal();

    if (std::abs(cosPlane) <= EPSILON) {
        return Intersection{}; // Parallel vector
    }
    Coordinates p0 = this->getOrigin() - ray.getOrigin();
    double coef = p0 * this->getNormal() / cosPlane;
    if (coef < EPSILON)
        return Intersection{};
    return Intersection{this, coef, ray.getOrigin() + ray.getVector() * coef};
}

std::string Plane::to_string() const {
    return fmt::format("Plane(Center : {} ; Normal {} ; Color {})",
                       this->origin, this->normalVec, this->col);
}
