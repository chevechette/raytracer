#include "bhv.h"
#include "logger.h"

BHV::BHV(std::shared_ptr<Sphere> obj) : storage(std::make_shared<Box>(obj)) {}
BHV::BHV(std::shared_ptr<Triangle> obj) : storage(std::make_shared<Box>(obj)) {}
BHV::BHV(std::shared_ptr<Box> obj) : storage(obj) {

    spdlog::info("Constructed BHV from Box");
    if (obj) {
        spdlog::info("Box origin: {} {} {}", obj->getOrigin().x,
                     obj->getOrigin().y, obj->getOrigin().z);
    } else {
        spdlog::info("Null box received!");
    }
}

// TODO: rework this, this is a mess Just use a loop
BHV::BHV(std::shared_ptr<BHV> one, std::shared_ptr<BHV> two,
         std::shared_ptr<BHV> three, std::shared_ptr<BHV> four)
    : leaves{one, two, three, four} {
    Box box1, box2;

    if (leaves[0] != nullptr && leaves[1] != nullptr) {
        box1 = Box(*(leaves[0]->getBox()), *(leaves[1]->getBox()));
    } else if (leaves[0] != nullptr) {
        box2 = *leaves[0]->getBox();
    }
    if (leaves[2] != nullptr && leaves[3] != nullptr) {
        box2 = Box(*leaves[2]->getBox(), *leaves[3]->getBox());
    } else if (leaves[2] != nullptr) {
        box2 = *leaves[2]->getBox();
    }
    this->storage = std::make_shared<Box>(box1, box2);
    spdlog::debug("Build a BHV Branch such as : {}", this->to_string());
}

std::shared_ptr<Box> BHV::getBox() const {
    return this->storage;
}

BHV::~BHV() {
    spdlog::info("{} has been destroyed", this->to_string());
}

std::string BHV::to_string() const {
    std::string innerBox = (this->storage) ? this->storage->to_string() : std::string("No Box");

    return fmt::format("BHV Node ({} leaves :\n\tInner {})", this->countLeaves(), innerBox);
}

int BHV::countLeaves() const {
    int leafnb = 0;
    for (int i = 0; i < BHV_LEAVES_NUMBER; i++) {
        if (this->leaves[i])
            leafnb++;
    }
    return leafnb;
}

Intersection BHV::intersectNodeBox(const Ray &ray) const {

    Intersection closest{};

    // This is the basic logic
    // TODO: should be updated with a spatial tree later
    Intersection selfintersect = this->storage->intersect(ray);
    if (selfintersect) {
        if (this->storage->hasObj()) {
            return this->storage->intersect(ray);
        }
        return this->intersectSubNodes(ray);
    }
    return Intersection{};
}

Intersection BHV::intersectSubNodes(const Ray &ray) const {
    Intersection innerClosest{};

    for (int i = 0; i < BHV_LEAVES_NUMBER; i++) {
        auto leafPtr = this->leaves[i];
        if (leafPtr != nullptr) {
            auto leafIntersect = leafPtr->intersectNodeBox(ray);
            if (leafIntersect && leafIntersect < innerClosest) {
                innerClosest = leafIntersect;
            }
        }
    }
    return innerClosest;
}