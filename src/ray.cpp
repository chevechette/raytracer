#include <cmath>

#include "structs.h"
#include "ray.h"

Ray::Ray() {
    Ray(0, 0, 0, 0, 0, 0, 0xFFFFFFFF);
}

Ray::Ray(float x, float y, float z, float a, float b, float c) {
    *this = Ray(x, y, z, a, b, c, 0xFFFFFFFF);
}

Ray::Ray(float x, float y, float z, float a, float b, float c, float hexcolor) {
    *this = Ray(Coordinates{x, y, z}, Coordinates{a, b, c}, hexcolor);
}

Ray::Ray(Coordinates loc, Coordinates vec) {
    *this = Ray(loc, vec, Color{1, 1, 1, 1});
}

Ray::Ray(Coordinates loc, Coordinates vec, float hexcolor) {
    float    red, green, blue, alpha = 1.0;

    blue = fmod(hexcolor, 0x100);
    hexcolor -= blue;
    green = floor(fmod(hexcolor, 0x100));
    hexcolor -= green;
    red = floor(fmod(hexcolor, 0x100));
    hexcolor -= red;
    alpha = floor(fmod(hexcolor, 0x100));
    Color col = {
        .r = red / 0x100, .g = green / 0x100, .b = blue / 0x100, .a = alpha / 0x100
    };
    *this = Ray(loc, vec, col);
}
   
Ray::Ray(Coordinates loc, Coordinates vec, Color col) {
    this->setColor(col);
    this->setOrigin(loc);
    this->setVector(vec);
    this->setLux(1.0);
}

Ray::~Ray() {

}

void Ray::setOrigin(float x, float y, float z) {
    this->setOrigin(Coordinates{x, y, z});
}

void Ray::setOrigin(Coordinates loc) {
    this->origin = loc;
}

void Ray::setVector(float x, float y, float z) {
    this->setVector(Coordinates{x, y, z});
}

void Ray::setVector(Coordinates vec) {
    this->vector = vec;
}

void Ray::setColor(float r, float g, float b, float a) {
    this->setColor(Color{r, g, b, a});
}

void Ray::setColor(Color col) {
    col.r = abs(col.r);
    col.g = abs(col.g);
    col.b = abs(col.b);
    col.a = abs(col.a);
    this->col = col;
}

void    Ray::setLux(float intensity) {
    this->lux = intensity;
}

Coordinates Ray::getOrigin() const {
    return this->origin;
}

Coordinates Ray::getVector() const {
    return this->vector;
}

Color       Ray::getColor() const {
    return this->col;
}

float       Ray::getLux() const {
    return this->lux;
}

// Checks
bool    Ray::isLight() const {
    return (this->lux >= RAY_LIGHT_THRESHOLD); 
}