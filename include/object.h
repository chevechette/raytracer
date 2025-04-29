#pragma once

#include "structs.h"
#include "ray.h"

class Object {
    protected:
        Color       col;
    public :
        virtual Coordinates intersect(Ray);
};