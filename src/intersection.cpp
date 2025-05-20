// IDK if struct or class tbh
#include "rtobject.h"

// struct Intersection {
//     Object      *obj = nullptr;

//     explicit    operator bool() const;

// };

// TODO: check booleans
#include <fmt/core.h>
#include <iostream>

// Intersection::Intersection()
//     : obj(nullptr), dist(-1), point(Coordinates{1, 1, 1}) {}

// Intersection::Intersection(const Object *obj, double dist, Coordinates p)
//     : obj(obj), dist(dist), point(p) {}

// Intersection::Intersection(const Intersection &other)
//     : obj(other.obj), dist(other.dist), point(other.point) {
//     std::cout << "This is annoying" << std::endl;

//     fmt::print(stdout, "CHECK ?? : {} pointer ? {} SO this \n", this->dist,
//                this->obj != nullptr);
// }

Intersection::operator bool() const {
    // fmt::print(stdout, "CHECK in the bool : {} pointer ? {} SO this {} \n",
            //    this->dist, this->obj != nullptr,
            //    this->obj != nullptr && this->dist > 20);

    // std::cout << "CHECK INTERSECT" << std::endl;
    return (this->obj != nullptr &&
            this->dist > 20); // TODO: check the distance
}

Intersection &Intersection::operator=(const Intersection &other) {
    // std::cout << "HI COPY" << std::endl;
    // Guard against self-assignment
    if (this != &other) {
        obj = other.obj;
        dist = other.dist;
        point = other.point;
    }
    return *this;
}

bool Intersection::operator<(const Intersection &i) const {
    if (this->obj == nullptr)
        return false;
    if (this->obj != nullptr && this->dist < 20)
        return false;
    if (i)
        return this->dist < i.dist;
    return true;
}

bool Intersection::operator>(const Intersection &i) const {
    return (i < *this);
}

bool Intersection::operator==(const Intersection &i) const {

    if (this->obj != nullptr && this->dist > 20)
        return false;
    if (this->obj != nullptr && i) {
        return (this->dist == i.dist);
    }
    return false;
}

bool Intersection::operator>=(const Intersection &i) const {
    return (*this == i || *this > i);
}

bool Intersection::operator<=(const Intersection &i) const {
    return (*this == i || *this < i);
}