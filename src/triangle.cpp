#include "object.h"

Triangle::Triangle(Coordinates a, Coordinates b, Coordinates c) :
    Object(a, Color{0, 0, 0, 0}) {
}

Triangle::Triangle(Coordinates a, Coordinates b, Coordinates c, Color col) :
    Object(a, col) {
}

Triangle::~Triangle() {
}

void    Triangle::setVertexA(float x, float y, float z) {
    this->setVertexA(Coordinates{x, y, z});
}

void    Triangle::setVertexA(Coordinates vertex) {
    this->setVertex(this->a, vertex);
}

void    Triangle::setVertexB(float x, float y, float z) {
    this->setVertexB(Coordinates{x, y, z});
}

void    Triangle::setVertexB(Coordinates vertex) {
    this->setVertex(this->b, vertex);
}

void    Triangle::setVertexC(float x, float y, float z) {
    this->setVertexC(Coordinates{x, y, z});
}

void    Triangle::setVertexC(Coordinates vertex) {
    this->setVertex(this->c, vertex);
}

void    Triangle::setVertex(Coordinates &ref, Coordinates &point) {
    ref = point;
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

Coordinates Triangle::intersect(Ray ray) const {
    return Coordinates{0, 0, 0}; // TODO: Triangle interesect place holder
}