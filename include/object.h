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

        virtual Intersection intersect(const Ray &ray) const = 0;

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

        Intersection intersect(Ray) const;
};

class Triangle : public Object {
    private:
        Coordinates a;
        Coordinates b;
        Coordinates c;

        Coordinates normal;

        static void        setVertex(Coordinates &ref, Coordinates &point);
        static Coordinates getCenter(Coordinates a, Coordinates b, Coordinates c);
        void    setNormal();
    
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

        Intersection intersect(const Ray &ray) const;
};



class Plane : public Object {
    private:
        Coordinates normalVec;
        float       height;  
        float       width;
        Coordinates h;
        Coordinates w;

        void        setVectors();

    public:    
        Plane(Coordinates origin, Coordinates normal);
        Plane(Coordinates origin, Coordinates normal, Color col);
        Plane(Coordinates origin, Coordinates normal, float height, float width);
        Plane(Coordinates origin, Coordinates normal, Color col, float height, float width);
        ~Plane();
 
        void        setNormal(Coordinates norm);
        Coordinates getNormal() const;
        void        setHeight(float x);
        void        setwidth(float x);
        float       getHeight(float x) const;
        float       getwidth(float x) const;

        
        bool    checkHeight(const Coordinates &v) const;
        bool    checkWidth(const Coordinates &v) const;

        Intersection intersect(const Ray &ray) const;
};