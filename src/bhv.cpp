#include "bhv.h"

BHV::BHV(std::shared_ptr<Sphere> obj) : storage(obj) {}
BHV::BHV(std::shared_ptr<Triangle> obj) : storage(obj) {}
BHV::BHV(const Box &obj) : storage(obj) {
  
    if (!storage.hasObj()) {
        std::cerr << "BHV constructed with box that has null obj!" << std::endl;
        std::terminate(); // Or throw std::runtime_error
    }
}

// TODO: rework this, this is a mess Just use a loop
BHV::BHV(std::shared_ptr<BHV> one, std::shared_ptr<BHV> two,
    std::shared_ptr<BHV> three, std::shared_ptr<BHV> four)
    : leaf1(one), leaf2(two), leaf3(three), leaf4(four) {
    Box box1, box2;

    if (leaf1 != nullptr && leaf2 != nullptr) {
        box1 = Box(leaf1->getBox(), leaf2->getBox());
    } else if (leaf1 != nullptr) {
        box2 = leaf1->getBox();
    }
    if (leaf3 != nullptr && leaf4 != nullptr) {
        box2 = Box(leaf3->getBox(), leaf4->getBox());
    } else if (leaf3 != nullptr) {
        box2 = leaf3->getBox();
    }
    this->storage = Box(box1, box2);
}

const Box &BHV::getBox() const {
    return this->storage;
}

#include <iostream>
BHV::~BHV() {
    std::cout << "Node has been destroyed" << std::endl;
}