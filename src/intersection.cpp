// IDK if struct or class tbh
#include "object.h"

// struct Interesction {
//     Object      *obj = nullptr;

//     explicit    operator bool() const;

// };

Interesction::operator bool() const {
    return (this->obj != nullptr);
}

bool Interesction::operator<(const Interesction &i) const {
    if (this->obj == nullptr)
        return false;
    if (i)
        return this->dist < i.dist;
    return false;
}

bool Interesction::operator>(const Interesction &i) const {
    return (i < *this);
}

bool Interesction::operator==(const Interesction &i) const {
    if (this->obj != nullptr && i) {
        return (this->dist == i.dist);
    }
    return false;
}

bool Interesction::operator>=(const Interesction &i) const {
    return (*this == i || *this > i);
}

bool Interesction::operator<=(const Interesction &i) const {
    return (*this == i || *this < i);
}