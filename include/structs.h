#pragma once

#include <cstdlib>

// TODO: Default constructors ? 
#include "forward_declaration.h"

struct Color {
    float  r;
    float  g;
    float  b;
    float  a = 1;

    // TODO: update the random to something safer rand has issue and has been updated in c++11
    // I initialised the seed in main.cpp
    inline static Color    random() {
        return Color{static_cast <float>(std::rand() % 0x100) / 0x100f,
            static_cast <float>(std::rand() % 0x100) / 0x100f,
            static_cast <float>(std::rand() % 0x100) / 0x100f};
    }
};

struct Coordinates {
    float   x;
    float   y;
    float   z;

    // double or float ? what is better for precision ?
    // dot operator
    inline    double operator*(Coordinates &v) const {
        double  res = 0;

        res += this->x * v.x;
        res += this->y * v.y;
        res += this->z * v.z;
        return res;
    }

    inline  Coordinates operator+(const Coordinates &v) const {
        return Coordinates{this->x + v.x, this->y +  v.y, this->z * v.z};
    }
    
    inline  Coordinates operator-(const Coordinates &v) const {
        return Coordinates{this->x - v.x, this->y -  v.y, this->z - v.z};
    }
};

// Given all operators, maybe it should become a class;
struct Interesction {
    Object      *obj = nullptr;
    float       dist = -1;
    Coordinates point = {0, 0, 0};

    explicit    operator bool() const;

    // Logical operators to compare distance quickly
    bool operator<(const Interesction &i) const;
    bool operator>(const Interesction &i) const;
    bool operator==(const Interesction &i) const;
    bool operator>=(const Interesction &i) const;
    bool operator<=(const Interesction &i) const;
};

// Create a new struct for intersections with distance and other data ?
