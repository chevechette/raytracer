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
        inline  void estimateCenter() {}
    public:
        ObjectAggregation();
        ~ObjectAggregation();

        Intersection     intersect(Ray ray) const;
        //         virtual Coordinates intersect(Ray) const = 0;
};

ObjectAggregation::ObjectAggregation() :
    Object(Coordinates{0, 0, 0}, Color::random()) {

}

ObjectAggregation::~ObjectAggregation() {

}

Intersection ObjectAggregation::intersect(Ray ray) const {
    return Intersection{}; // TODO: Plane interesect place holder
}