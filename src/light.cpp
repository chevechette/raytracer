#include "light.h"
#include "managers.h"
#include "structs.h"

Light::Light(const Coordinates &posdir, const Color &col, float lux)
    : posdir(posdir), col(col), lux(lux) {}

Light::Light(const Coordinates &posdir, const Color &col)
    : posdir(posdir), col(col) {}

Light::~Light() {}

void Light::setColor(const Color &col) {
    this->col = col;
}

void Light::setLux(float luxpower) {
    if (luxpower > 1 || luxpower < 0)
        return;
    this->lux = luxpower;
}

void Light::setCoordinates(const Coordinates &pos) {
    this->posdir = pos;
}

Color Light::getColor() const {
    return this->col;
}

float Light::getLux() const {
    return this->lux;
}

// TODO: update this for relative lux power
Color Light::getLuxedColor() const {
    Color c = this->col;
    c.a = this->lux;
    return c;
}

LightType Light::getType() const {
    return this->ltype;
}

Coordinates Light::getLightDir(const Coordinates &point) const {
    return (this->posdir - point).normalize();
}

double Light::getLightDist(const Coordinates &point) const {
    Coordinates distance = this->posdir - point;
    return distance.abs();
}

DistantLight::DistantLight(const Coordinates &posdir, const Color &col,
                           float lux)
    : Light(posdir, col, lux) {}

DistantLight::DistantLight(const Coordinates &posdir, const Color &col)
    : Light(posdir, col) {}

DistantLight::~DistantLight() {}

#include "logger.h"

// TODO: fix this
bool DistantLight::illuminate(const Coordinates &from) const {
    Coordinates dir = -this->posdir;
    // dir = Coordinates{0, 0, 1};
    // double maxdist = this->getLightDist(from);
    Ray ray = Ray(from, dir);

    ObjectManager &objmanager = ObjectManager::getInstance();
    Intersection intersect = objmanager.treeWalk(ray);
    if (intersect) {
        // spdlog::info("No lighting");
        // spdlog::debug("DISTANCE no light {}", intersect.dist);
        return false;
    }
    // if (intersect.dist <= EPSILON)
    //     return false;
    //  && intersect.dist < maxdist)
    // spdlog::debug("distance {} from point {} light dir {}", intersect.dist,
    //               from, dir);
    return true;
}