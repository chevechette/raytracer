#include "structs.h"
#include "object.h"

Triangle::Triangle(Coordinates a, Coordinates b, Coordinates c) :
    Object(Triangle::getCenter(a, b, c), Color{1, 1, 1, 1}) {
}

Triangle::Triangle(Coordinates a, Coordinates b, Coordinates c, Color col) :
    Object(Triangle::getCenter(a, b, c), col) {
}

Triangle::~Triangle() {
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

Interesction Triangle::intersect(Ray ray) const {
    return Interesction{}; // TODO: Plane interesect place holder
}