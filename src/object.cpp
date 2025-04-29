// interface object
// sphere triangle and plane as inheritance
// wabout cameras ?

#include <cmath>
#include "object.h"

// class Object {
//     protected:
//         explicit    Object(Coordinates origin, Color col);
        
//         Color       col;
//         Coordinates origin;
//     public :
//         virtual ~Object();

//         virtual Coordinates intersect(Ray) const = 0;

//         void        setColor(Color col);
//         void        setOrigin(Coordinates origin);
//         Color       getColor() const;
//         Coordinates getOrigin() const;
// };

Object::Object(Coordinates origin, Color col) {
    this->setOrigin(origin);
    this->setColor(col);
}

Object::~Object() {
    
}

void    Object::setColor(Color col) {
    this->col = col;
}

Color   Object::getColor() const {
    return this->col;
}

void    Object::setOrigin(Coordinates origin) {
    this->origin = origin;
}

Coordinates   Object::getOrigin() const {
    return this->origin;
}

class ObjectAggregation : public Object {
    private:
        // vector of objects
    public:
        ObjectAggregation();
        ~ObjectAggregation();

        Coordinates     intersect(Ray ray) const;
        //         virtual Coordinates intersect(Ray) const = 0;
};

ObjectAggregation::ObjectAggregation() :
    Object(Coordinates{0, 0, 0, false}, Color{1, 1, 1, 1}) {

}

ObjectAggregation::~ObjectAggregation() {

}

Coordinates ObjectAggregation::intersect(Ray ray) const {
    return Coordinates{0, 0, 0, false}; // TODO: Plane interesect place holder
}