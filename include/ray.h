#include "structs.h"
#pragma once

class Ray {
    private :
        Coordinates origin;
        Coordinates vector;
        Color       col;
    public :
        Ray();
        Ray(float x, float y, float z, float a, float b, float c);
        Ray(float x, float y, float z, float a, float b, float c, float hexcolor);
        Ray(Coordinates loc, Coordinates vec);
        Ray(Coordinates loc, Coordinates vec, Color col);
        Ray(Coordinates loc, Coordinates vec, float hexcolor);
        ~Ray();
        void setOrigin(float x, float y, float z);
        void setOrigin(Coordinates loc);
        void setVector(float x, float y, float z);
        void setVector(Coordinates loc);
        void setColor(float r, float g, float b, float a);
        void setColor(Color loc);

        Coordinates getOrigin();
        Coordinates getVector();
        Color       getColor();
};