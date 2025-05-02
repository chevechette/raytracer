// IDK if struct or class tbh
#include "object.h"

// struct Interesction {
//     Object      *obj = nullptr;

//     explicit    operator bool() const;

// };

Interesction::operator bool() const {
    return (this->obj != nullptr);
}
