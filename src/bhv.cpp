#include "bhv.h"

BHV::BHV(std::shared_ptr<Sphere> obj) : storage(std::make_shared<Box>(obj)) {}
BHV::BHV(std::shared_ptr<Triangle> obj) : storage(std::make_shared<Box>(obj)) {}
BHV::BHV(std::shared_ptr<Box> obj) : storage(obj) {

    std::cout << "Constructed BHV from Box" << std::endl;
    if (obj) {
        std::cout << "Box origin: " << obj->getOrigin().x << std::endl;
    } else {
        std::cout << "Null box received!" << std::endl;
    }
}

// TODO: rework this, this is a mess Just use a loop
BHV::BHV(std::shared_ptr<BHV> one, std::shared_ptr<BHV> two,
         std::shared_ptr<BHV> three, std::shared_ptr<BHV> four)
    : leaf1(one), leaf2(two), leaf3(three), leaf4(four) {
    Box box1, box2;

    if (leaf1 != nullptr && leaf2 != nullptr) {
        box1 = Box(*leaf1->getBox(), *leaf2->getBox());
    } else if (leaf1 != nullptr) {
        box2 = *leaf1->getBox();
    }
    if (leaf3 != nullptr && leaf4 != nullptr) {
        box2 = Box(*leaf3->getBox(), *leaf4->getBox());
    } else if (leaf3 != nullptr) {
        box2 = *leaf3->getBox();
    }
    this->storage = std::make_shared<Box>(box1, box2);
}

std::shared_ptr<Box> BHV::getBox() const {
    return this->storage;
}

#include <iostream>
BHV::~BHV() {
    std::cout << "Node has been destroyed" << std::endl;
}