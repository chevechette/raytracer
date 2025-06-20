// interface object

#include "logger.h"
#include "rtobject.h"
#include <cmath>

// Exception checked

Object::Object(Coordinates origin, Color col) {
    this->setOrigin(origin);
    this->setColor(col);
}

Object::~Object() {
}

void Object::setColor(Color col) {
    this->col = col;
}

Color Object::getColor() const {
    return this->col;
}

void Object::setOrigin(Coordinates origin) {
    this->origin = origin;
}

Coordinates Object::getOrigin() const {
    return this->origin;
}

// class ObjectAggregation : public Object {
//   private:
//     // vector of objects
//     inline void estimateCenter() {}

//   public:
//     ObjectAggregation();
//     ~ObjectAggregation();

//     Intersection intersect(Ray ray) const;
//     //         virtual Coordinates intersect(Ray) const = 0;
// };

// ObjectAggregation::ObjectAggregation()
//     : Object(Coordinates{0, 0, 0}, Color::random()) {}

// ObjectAggregation::~ObjectAggregation() {}

// Intersection ObjectAggregation::intersect(Ray ray) const {
//     return Intersection{}; // TODO: Plane interesect place holder
// }