#include "structs.h"
#include "rtobject.h"

Triangle::Triangle(Coordinates a, Coordinates b, Coordinates c) :
    Object(Triangle::getCenter(a, b, c), Color{1, 1, 1, 1}) {
        this->setNormal();
}

Triangle::Triangle(Coordinates a, Coordinates b, Coordinates c, Color col) :
    Object(Triangle::getCenter(a, b, c), col) {
        this->setNormal();
}

Triangle::~Triangle() {
}

void    Triangle::setNormal() {
    this->normal = (this->b - this->a) ^ (this->c - this->a);
}

void    Triangle::setVertexA(float x, float y, float z) {
    this->setVertexA(Coordinates{x, y, z});
}

void    Triangle::setVertexA(Coordinates vertex) {
    Triangle::setVertex(this->a, vertex);
}

void    Triangle::setVertexB(float x, float y, float z) {
    this->setVertexB(Coordinates{x, y, z});
}

void    Triangle::setVertexB(Coordinates vertex) {
    Triangle::setVertex(this->b, vertex);
}

void    Triangle::setVertexC(float x, float y, float z) {
    this->setVertexC(Coordinates{x, y, z});
}

void    Triangle::setVertexC(Coordinates vertex) {
    Triangle::setVertex(this->c, vertex);
}

void    Triangle::setVertex(Coordinates &ref, Coordinates &point) {
    ref = point;
}

Coordinates Triangle::getCenter(Coordinates a, Coordinates b, Coordinates c) {
    return Coordinates{
        ((a.x + b.x + c.x) / 3.0f), ((a.y + b.y + c.y) / 3.0f), ((a.z + b.z + c.z) / 3.0f)
    };
}

Coordinates Triangle::getVertexA() const {
    return this->a;
}

Coordinates Triangle::getVertexB() const {
    return this->b;
}

Coordinates Triangle::getVertexC() const {
    return this->c;
}

// maybe this should be using some inheritance from Plane
Intersection Triangle::intersect(const Ray &ray) const {    
    double dot = this->normal * ray.getVector();
    if (dot == 0)
        return Intersection{};
        
    Coordinates p0 = this->getOrigin() - ray.getOrigin();
    double  coef = p0 * this->normal / dot; // this is the multiplier of the vector

    // edges
    Coordinates e = this->b - this->a;
    Coordinates f = this->c - this->a;
    // barocentric ponderation
    double u = (p0 * (ray.getVector() ^ f)) / dot;
    double v = (p0 * (ray.getVector() ^ e)) / dot;
    if (u < 0.0 || u > 1.0 || v < 0.0 || (u + v) > 1)
        return Intersection{};
    return Intersection{this, coef, ray.getOrigin() + ray.getVector() * coef};
}