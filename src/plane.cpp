#include "structs.h"
#include "object.h"

Plane::Plane(Coordinates origin, Coordinates normal) :
    Object(origin, Color{1, 1, 1, 1}), normalVec{normal}, height{-1}, width{-1} {
    this->setVectors();
}

Plane::Plane(Coordinates origin, Coordinates normal, Color col) :
    Object(origin, col), normalVec{normal}, height{-1}, width{-1}  {
    this->setVectors();
}

Plane::Plane(Coordinates origin, Coordinates normal, float height, float width) :
    Object(origin, Color{1, 1, 1, 1}), normalVec{normal}, height{height}, width{width}  {
    this->setVectors();
}

Plane::Plane(Coordinates origin, Coordinates normal, Color col, float height, float width) :
    Object(origin, col), normalVec{normal}, height{height}, width{width}  {
    this->setVectors();
}

Plane::~Plane() {

}

void    Plane::setNormal(Coordinates norm) {
    this->normalVec = norm;
}

Coordinates Plane::getNormal() const {
    return this->normalVec;
}

void    Plane::setVectors() {
    Coordinates vec = (std::abs(this->normalVec.x) < std::abs(this->normalVec.y)) ?
        Coordinates{0, 1, 0 } : Coordinates{0, 0, 1 };
    this->h = this->normalVec ^ vec;
    this->w = this->normalVec ^ this->h;
}

bool    Plane::checkHeight(const Coordinates &v) const {
    if (this->height <= 0)
        return true;
    return ((this->h * v) <= height);

}

bool    Plane::checkWidth(const Coordinates &v) const {
    if (this->width <= 0)
        return true;
    return ((this->w * v) <= width);

}

float       Plane::getHeight(float x) const {
    return this->height;
}

float       Plane::getwidth(float x) const {
    return this->width;
}

Intersection Plane::intersect(const Ray &ray) const {
    double cosPlane = ray.getVector() * this->getNormal();
    if (cosPlane == 0) {
        return Intersection{}; // Parallel vector
    }
    Coordinates p0 = this->getOrigin() - ray.getOrigin();
    double  coef = p0 * this->getNormal() / cosPlane;

    // TODO : check this
    if (this->height > 0 && (p0 - this->origin) * this->h > this->height) {
        return Intersection{};
    }
    if (this->width > 0 && (p0 - this->origin) * this->w > this->width) {
        return Intersection{};
    }

    return Intersection{this, coef, ray.getOrigin() + ray.getVector() * coef};
}