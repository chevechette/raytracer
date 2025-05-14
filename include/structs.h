#pragma once

#include <cmath>
#include <cstdlib>

// TODO: Default constructors ?
#include "forward_declaration.h"

// TODO : check all normalisation for vectors

struct Color {
    float r;
    float g;
    float b;
    float a = 1;

    // TODO: update the random to something safer rand has issue and has been
    // updated in c++11 I initialised the seed in main.cpp
    inline static Color random() {
        return Color{static_cast<float>(std::rand() % 0x100) / 0xFFf,
                     static_cast<float>(std::rand() % 0x100) / 0xFFf,
                     static_cast<float>(std::rand() % 0x100) / 0xFFf};
    }

    inline static Color fromHexAlpha(unsigned int col) {
        return Color{(col / 0x1000000 % 0x100) * 1.0f / 0xFF,
                     (col / 0x10000 % 0x100) * 1.0f / 0xFF,
                     (col / 0x100 % 0x100) * 1.0f / 0xFF,
                     (col % 0x100) * 1.0f / 0xFF};
    }

    inline static Color fromHex(unsigned int col) {
        return Color::fromHexAlpha(col * 0x100 + 0xFF);
    }
};

// this is soon eight going to be an hpp file or a class
struct Coordinates {
    float x;
    float y;
    float z;

    inline Coordinates operator+(const Coordinates &v) const {
        return Coordinates{this->x + v.x, this->y + v.y, this->z * v.z};
    }

    inline Coordinates operator-() const {
        return Coordinates{-this->x, -this->y, -this->z};
    }

    inline Coordinates operator-(const Coordinates &v) const {
        return Coordinates{this->x - v.x, this->y - v.y, this->z - v.z};
    }

    // Scalar product
    inline Coordinates operator*(const float coef) const {
        return Coordinates{this->x * coef, this->y * coef, this->z * coef};
    }

    // dot product
    inline double operator*(const Coordinates &v) const {
        double res = 0;

        res += this->x * v.x;
        res += this->y * v.y;
        res += this->z * v.z;
        return res;
    }

    // Cross product
    inline Coordinates operator^(const Coordinates &v) const {
        return Coordinates{this->y * v.z - this->z * v.y,
                           this->z * v.x - this->x * v.z,
                           this->x * v.y - this->y * v.x};
    }

    // should this not modify ? most operation always need permanent
    // normalization
    inline Coordinates &normalize() {
        auto length =
            sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        this->x = this->x / length;
        this->y = this->y / length;
        this->z = this->z / length;
        // how to normalize a vector?
        return *this;
    }
};

// Given all operators, maybe it should become a class;
// No normal, or rebound calculation yet
struct Intersection {
    const Object *obj = nullptr;
    double dist = -1;
    Coordinates point = Coordinates{0, 0, 0};

    explicit operator bool() const;

    // Logical operators to compare distance quickly
    bool operator<(const Intersection &i) const;
    bool operator>(const Intersection &i) const;
    bool operator==(const Intersection &i) const;
    bool operator>=(const Intersection &i) const;
    bool operator<=(const Intersection &i) const;
};

// Create a new struct for intersections with distance and other data ?
