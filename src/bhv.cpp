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
    // std::cout << "Hi, imma make box" << std::endl;
    Box box1, box2;
    // if (leaves[0] != nullptr)
    //     std::cout << leaves[0]->getBox()->getOrigin().x << std::endl;
    // if (leaves[1] != nullptr)
    //     std::cout << leaves[1]->getBox()->getOrigin().x << std::endl;
    // if (leaves[2] != nullptr)
    //     std::cout << leaves[2]->getBox()->getOrigin().x << std::endl;
    // if (leaves[3] != nullptr)
    //     std::cout << leaves[3]->getBox()->getOrigin().x << std::endl;

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
    // std::cout << "Hi, imma did make box" << std::endl;
}

std::shared_ptr<Box> BHV::getBox() const {
    return this->storage;
}

#include <iostream>
BHV::~BHV() {
    spdlog::info("Node has been destroyed");
}

Intersection BHV::intersectNodeBox(const Ray &ray) const {

    Intersection closest{};

    // This is the basic logic
    // TODO: should be updated with a spatial tree later
    Intersection selfintersect = this->storage->intersect(ray);
    if (selfintersect) {
        if (this->storage->hasObj()) {
            // std::cout << "Intersecting with inner object" << std::endl;
            return this->storage->intersect(ray);
        }
        // std::cout << "Intersecting with leaves" << std::endl;
        return this->intersectSubNodes(ray);
    }
    return Intersection{};
}

Intersection BHV::intersectSubNodes(const Ray &ray) const {
    Intersection innerClosest{};

    // std::cout << "\t Box has been intersected proceed to check inner nodes"
    //           << std::endl;
    for (int i = 0; i < BHV_LEAVES_NUMBER; i++) {
        auto leafPtr = this->leaves[i];
        if (leafPtr != nullptr) {
            auto leafIntersect = leafPtr->intersectNodeBox(ray);
            if (leafIntersect && leafIntersect < innerClosest) {
                innerClosest = leafIntersect;
                // std::cout << "intersection updated" << std::endl;
            }
        }
    }
    return innerClosest;
}