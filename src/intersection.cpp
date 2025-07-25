// IDK if struct or class tbh
#include "rtobject.h"

Intersection::operator bool() const {
    return (this->obj != nullptr &&
            this->dist > EPSILON);
}

Intersection &Intersection::operator=(const Intersection &other) {
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