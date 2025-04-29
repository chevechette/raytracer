#include "structs.h"
#include "ray.h"

Ray::Ray() {
    Ray(0, 0, 0, 0, 0, 0, 0xFFFFFFFF);
}

Ray::Ray(float x, float y, float z, float a, float b, float c) {
    Ray(x, y, z, a, b, c, 0xFFFFFFFF);
}

Ray::Ray(float x, float y, float z, float a, float b, float c, float hexcolor) {
    Ray(Coordinates{x, y, z}, Coordinates{a, b, c}, hexcolor);
}

Ray::Ray(Coordinates loc, Coordinates vec) {
    Ray(loc, vec, Color{1, 1, 1, 1});
}

Ray::Ray(Coordinates loc, Coordinates vec, float hexcolor) {
    Color col = {
        .r = 1, .g = 1, .b = 1, .a = hexcolor / 0x1000000
    };
    Ray(loc, vec, col);
}

Ray::Ray(Coordinates loc, Coordinates vec, Color col) {
    this->setColor(col);
    this->setOrigin(origin);
    this->setVector(vector);
}

Ray::~Ray() {

}

void Ray::setOrigin(float x, float y, float z) {

}

void Ray::setOrigin(Coordinates loc) {

}

void Ray::setVector(float x, float y, float z) {

}

void Ray::setVector(Coordinates loc) {
}

void Ray::setColor(float r, float g, float b, float a) {

}

void Ray::setColor(Color loc) {

}

Coordinates Ray::getOrigin() {
    return this->origin;
}

Coordinates Ray::getVector() {
    return this->vector;
}

Color       Ray::getColor() {
    return this->col;
}

