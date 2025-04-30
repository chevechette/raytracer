#include "structs.h"
#include "object.h"

Plane::Plane(Coordinates origin, Coordinates normal) :
    Object(origin, Color{1, 1, 1, 1}), normalVec{normal}, height{-1}, width{-1} {
}

Plane::Plane(Coordinates origin, Coordinates normal, Color col) :
    Object(origin, col), normalVec{normal}, height{-1}, width{-1}  {
}

Plane::Plane(Coordinates origin, Coordinates normal, float height, float width) :
    Object(origin, Color{1, 1, 1, 1}), normalVec{normal}, height{height}, width{width}  {
}

Plane::Plane(Coordinates origin, Coordinates normal, Color col, float height, float width) :
    Object(origin, col), normalVec{normal}, height{height}, width{width}  {
}

Plane::~Plane() {

}

void    Plane::setNormal(Coordinates norm) {
    this->normalVec = norm;
}

Coordinates Plane::getNormal() const {
    return this->normalVec;
}

float       Plane::getHeight(float x) const {
    return this->height;
}
float       Plane::getwidth(float x) const {
    return this->width;
}

Interesction Plane::intersect(Ray ray) const {
    return Interesction{}; // TODO: Plane interesect place holder
}