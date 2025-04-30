#pragma once

// Default constructors ? 
#include "forward_declaration.h"

struct Color {
    float  r;
    float  g;
    float  b;
    float  a;
};

struct Coordinates {
    float   x;
    float   y;
    float   z;
};

struct Interesction {
    Object      *obj = nullptr;

    explicit    operator bool() const;

};

// Create a new struct for intersections with distance and other data ?
