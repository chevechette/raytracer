#pragma once

#include "structs.h"
#include "ray.h"

class Object {
    protected:
        explicit    Object(Coordinates origin, Color col);
        
        Color       col;
        Coordinates origin;
    public :
        virtual ~Object();

        virtual Coordinates intersect(Ray) const = 0;

        void        setColor(Color col);
        void        setOrigin(Coordinates origin);
        Color       getColor() const;
        Coordinates getOrigin() const;
};

class Sphere : public Object {
    private:
        Coordinates origin;
        float       radius;

    public:
        Sphere(Coordinates pos, float radius);
        Sphere(Coordinates pos, float radius, Color col);
        ~Sphere();

        void        setRadius(float radius);
        float       getRadius() const;

        Coordinates intersect(Ray) const;
};

class Triangle : public Object {
    private:
        Coordinates a;
        Coordinates b;
        Coordinates c;

        static void        setVertex(Coordinates &ref, Coordinates &point);
        static Coordinates getCenter(Coordinates a, Coordinates b, Coordinates c);
    
    public:
        Triangle(Coordinates a, Coordinates b, Coordinates c);
        Triangle(Coordinates a, Coordinates b, Coordinates c, Color col);
        ~Triangle();

        void        setVertexA(float x, float y, float z);
        void        setVertexA(Coordinates vertex);
        void        setVertexB(float x, float y, float z);
        void        setVertexB(Coordinates vertex);
        void        setVertexC(float x, float y, float z);
        void        setVertexC(Coordinates vertex);
        Coordinates getVertexA() const;
        Coordinates getVertexB() const;
        Coordinates getVertexC() const;

        Coordinates intersect(Ray) const;
};