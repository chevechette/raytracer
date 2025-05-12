// IDK if struct or class tbh
#include "rtobject.h"

// struct Intersection {
//     Object      *obj = nullptr;

//     explicit    operator bool() const;

// };


// TODO: check booleans
Intersection::operator bool() const {
    return (this->obj != nullptr && this->dist > 20); // TODO: check the distance
}

bool Intersection::operator<(const Intersection &i) const {
    if (this->obj != nullptr && this->dist > 20)
        return false;
    if (this->obj == nullptr)
        return false;
    if (i)
        return this->dist < i.dist;
    return false;
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