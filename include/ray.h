#include "structs.h"
#pragma once

#define RAY_LIGHT_THRESHOLD 0.1 // This is a test threshold can go be set up as define or variable later
// how much does light intensity gets diffused or weakened with distance ?

// TODO: Const & ref check
class Ray {
    private :
        Coordinates origin;
        Coordinates vector;
        Color       col;
        float       lux;
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
        void setVector(Coordinates vec);
        void setColor(float r, float g, float b, float a);
        void setColor(Color loc);
        void setLux(float lum);

        Coordinates     getOrigin() const;
        Coordinates     getVector() const;
        Color           getColor() const;
        float           getLux() const;

        // Checks
        bool  isLight() const;

        //TODO: add operator creation ? copy, moving...change color...?

        //TODO: Define more fonction
};