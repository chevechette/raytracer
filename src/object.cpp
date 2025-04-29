// interface object
// sphere triangle and plane as inheritance
// wabout cameras ?

#include "object.h"

// class Object {
//     public :
//         virtual Coordinates intersect(Ray);
// };

class Sphere : public Object {
    private:
        Coordinates origin;
        float       radius;
};

class Triangle : public Object {
    private:
        Coordinates a;
        Coordinates b;
        Coordinates c;
};

class Plane : public Object {
    private:
        Coordinates origin;
        Coordinates normalVec;
};