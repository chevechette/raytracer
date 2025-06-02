#include "rtobject.h"
#include <algorithm>
#include <iostream>
#include <memory>

Box::Box()
    : Object(Coordinates{0, 0, 0}, Color::random()),
      minlier(Coordinates{0, 0, 0}), maxlier(Coordinates{0, 0, 0}),
      validBox(false) {}

Box::Box(const Coordinates &m, const Coordinates &n)
    : Object((m + n) * 0.5, Color::random()), minlier(m), maxlier(n),
      obj(nullptr) {}

Box::Box(const Coordinates &m, const Coordinates &n, const Color &col)
    : Object((m + n) * 0.5, col), minlier(m), maxlier(n), obj(nullptr) {}

Box::Box(std::shared_ptr<Sphere> sphere)
    : Object(sphere->getOrigin(), sphere->getColor()),
      obj(std::static_pointer_cast<Object>(sphere)),
      minlier(sphere->getOrigin() - Coordinates{sphere->getRadius(),
                                                sphere->getRadius(),
                                                sphere->getRadius()}),
      maxlier(sphere->getOrigin() + Coordinates{sphere->getRadius(),
                                                sphere->getRadius(),
                                                sphere->getRadius()}) {
    std::cout << "Box created for sphere at " << sphere->getOrigin().x
              << sphere->getOrigin().y << sphere->getOrigin().z << std::endl;
}

Box::Box(std::shared_ptr<Triangle> triangle)
    : Object(triangle->getOrigin(), triangle->getColor()),
      obj(std::static_pointer_cast<Object>(triangle)),
      minlier(Coordinates{
          std::min({triangle->getVertexA().x, triangle->getVertexB().x,
                    triangle->getVertexC().x}),
          std::min({triangle->getVertexA().y, triangle->getVertexB().y,
                    triangle->getVertexC().y}),
          std::min({triangle->getVertexA().z, triangle->getVertexB().z,
                    triangle->getVertexC().z})}),
      maxlier(Coordinates{
          std::max({triangle->getVertexA().x, triangle->getVertexB().x,
                    triangle->getVertexC().x}),
          std::max({triangle->getVertexA().y, triangle->getVertexB().y,
                    triangle->getVertexC().y}),
          std::max({triangle->getVertexA().z, triangle->getVertexB().z,
                    triangle->getVertexC().z})}) {}

Box::Box(const Box &smallbox1, const Box &smallbox2)
    : Object((smallbox1.getOrigin() + smallbox2.getOrigin()) * 0.5,
             smallbox1.getColor()),
      obj(nullptr) {
    std::cout << "ACTUALLY MAKING THE BIG BOX START" << std::endl;
    std::cout << smallbox1.getOrigin().x << std::endl;
    std::cout << smallbox2.getOrigin().x << std::endl;
    std::cout << smallbox1.isValid() << std::endl;
    std::cout << smallbox2.isValid() << std::endl;
    if (smallbox1.isValid() && smallbox2.isValid()) {
        this->minlier =
            Coordinates{std::min({smallbox1.getMin().x, smallbox2.getMin().x}),
                        std::min({smallbox1.getMin().y, smallbox2.getMin().y}),
                        std::min({smallbox1.getMin().z, smallbox2.getMin().z})};
        this->maxlier =
            Coordinates{std::max({smallbox1.getMax().x, smallbox2.getMax().x}),
                        std::max({smallbox1.getMax().y, smallbox2.getMax().y}),
                        std::max({smallbox1.getMax().z, smallbox2.getMax().z})};
    } else if (smallbox1.isValid()) {
        this->minlier = smallbox1.getMin();
        this->maxlier = smallbox1.getMax();
    } else if (smallbox2.isValid()) {
        this->minlier = smallbox2.getMin();
        this->maxlier = smallbox2.getMax();
    } else {
        this->minlier = Coordinates{0, 0, 0};
        this->maxlier = Coordinates{0, 0, 0};
        this->validBox = false;
    }
}

Box::~Box() {
    std::cout << "Box has been destroyed" << std::endl;
}

Coordinates Box::getMin() const {
    return this->minlier;
}

void Box::setMin(Coordinates newMin) {
    this->minlier = newMin;
    this->setOrigin((newMin + this->maxlier) * 0.5);
}

Coordinates Box::getMax() const {
    return this->maxlier;
}

void Box::setMax(Coordinates newMax) {
    this->maxlier = newMax;
    this->setOrigin((newMax + this->maxlier) * 0.5);
}

void Box::setMinMax(Coordinates newMin, Coordinates newMax) {
    this->maxlier = newMax;
    this->minlier = newMin;
    this->setOrigin((newMin + newMax) * 0.5);
}

Intersection Box::intersectBox(const Ray &ray) const {
    const Coordinates &orgn = ray.getOrigin();
    const Coordinates &dir = ray.getVector();

    // find out nearest / fahrest point
    Coordinates t0, t1;
    float coefmin, coefmax, coef = 0;

    t0 = this->minlier - orgn;
    t0.x = (dir.x) ? t0.x / dir.x : 0;
    t0.y = (dir.y) ? t0.y / dir.y : 0;
    t0.z = (dir.z) ? t0.z / dir.z : 0;

    t1 = this->maxlier - orgn;
    t1.x = (dir.x) ? t1.x / dir.x : 0;
    t1.y = (dir.y) ? t1.y / dir.y : 0;
    t1.z = (dir.z) ? t1.z / dir.z : 0;

    if (t0.x > t1.x)
        std::swap(t0.x, t1.x);
    if (t0.y > t1.y)
        std::swap(t0.y, t1.y);
    if (t0.z > t1.z)
        std::swap(t0.z, t1.z);

    if (dir.x == 0) {
        if (orgn.x < this->minlier.x || orgn.x > this->maxlier.x)
            return Intersection{};
        t0.x = t0.y;
        t1.x = t1.y;
    }
    if (dir.y == 0) {
        if (orgn.y < this->minlier.y || orgn.y > this->maxlier.y)
            return Intersection{};
        t0.y = t0.z;
        t1.y = t1.z;
    }
    if (dir.z == 0) {
        if (orgn.z < this->minlier.z || orgn.z > this->maxlier.z)
            return Intersection{};
        t0.z = t0.x;
        t1.z = t1.x;
        if (dir.x == 0 && dir.y == 0)
            return Intersection{};
    }
    coefmin = std::max({t0.x, t0.y, t0.z});
    coefmax = std::min({t1.x, t1.y, t1.z});
    if (coefmin > coefmax)
        return Intersection{};
    coef = (coefmin < 0) ? coefmax : coefmin;
    if (coef < 0)
        return Intersection{};

    return Intersection{this, coef, orgn + (dir)*coef};
}

Intersection Box::intersectInnerObject(const Ray &ray) const {
    if (this->obj)
        return this->obj->intersect(ray);
    return Intersection{};
}

Intersection Box::intersect(const Ray &ray) const {
    if (this->obj)
        return this->intersectInnerObject(ray);
    return this->intersectBox(ray);
}
bool Box::hasObj() const {
    return this->obj != nullptr;
}

const std::shared_ptr<const Object> Box::getObj() const {
    if (this->obj !=
        nullptr) // obj not nullptr ... I know I could remove this logic at all;
        return this->obj;
    return nullptr;
}

bool Box::isValid() const {
    return this->validBox;
}