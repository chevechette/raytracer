#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

// TODO: Default constructors ?
#include "forward_declaration.h"

// TODO : check all normalisation for vectors

struct Color {
    float r;
    float g;
    float b;
    float a = 1;

    // TODO: update the random to something safer rand has issue and has been
    // updated in c++11
    // I initialised the seed in main.cpp drom the load of the GUIManager
    inline static Color random() {
        float r, g, b;

        r = (std::rand() % 0x100);
        g = (std::rand() % 0x100);
        b = (std::rand() % 0x100);

        // this is just 255.0f in a very dramatic way
        return Color{r / 0xFF.0p0f, g / 0xFF.0p0f, b / 0xFF.0p0f};
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
        return Coordinates{this->x + v.x, this->y + v.y, this->z + v.z};
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

    inline bool operator>(const float check) const {
        return (this->x > check && this->y > check && this->z > check);
    }

    inline bool operator<(const float check) const {
        return (this->x < check && this->y < check && this->z < check);
    }

    inline bool operator==(const float check) const {
        return (this->x == check && this->y == check && this->z == check);
    }

    inline bool operator>=(const float check) const {
        return (*this > check && *this == check);
    }

    inline bool operator<=(const float check) const {
        return (*this < check && *this == check);
    }

    // #include <cmath>
    // normalization

    inline double abs() {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    inline Coordinates &normalizeSelf() {
        double length =
            sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        // std::cout << length << std::endl;
        if (length == 0)
            return *this;
        this->x = this->x / length;
        this->y = this->y / length;
        this->z = this->z / length;

        return *this;
    }

    inline Coordinates normalize() const {
        double length = sqrt((this->x * this->x) + (this->y * this->y) +
                             (this->z * this->z));

        if (length == 0)
            return Coordinates{0, 0, 0};

        Coordinates ret;

        ret.x = this->x / length;
        ret.y = this->y / length;
        ret.z = this->z / length;
        return ret;
    }
};

// Given all operators, maybe it should become a class;
// No normal, or rebound calculation yet
struct Intersection {
    const Object *obj = nullptr;
    double dist = -1;
    Coordinates point = Coordinates{0, 0, 0};

    // Intersection();
    // Intersection(const Object *obj, double dist, Coordinates p);
    // // Intersection(const Intersection& other) = default;
    // Intersection(const Intersection& i);
    Intersection &operator=(const Intersection &other);

    explicit operator bool() const;

    // Logical operators to compare distance quickly
    bool operator<(const Intersection &i) const;
    bool operator>(const Intersection &i) const;
    bool operator==(const Intersection &i) const;
    bool operator>=(const Intersection &i) const;
    bool operator<=(const Intersection &i) const;
};

// Create a new struct for intersections with distance and other data ?
