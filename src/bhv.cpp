#include "bhv.h"

// TODO : create leafnote
class BHV {
  private:
    Box storage;
    const BHV *leaf1 = nullptr;
    const BHV *leaf2 = nullptr;
    const BHV *leaf3 = nullptr;
    const BHV *leaf4 = nullptr;

  public:
    //    BHV();
    BHV(const Sphere &obj);
    BHV(const Triangle &obj);
    BHV(const Box &obj); // this does not copy the box's content into it...
                         // though it could ?

    BHV(const BHV *one, const BHV *two = nullptr, const BHV *three = nullptr,
        const BHV *four = nullptr);

    const Box &getBox() const;

    ~BHV();
};

BHV::BHV(const Sphere &obj) : storage(obj) {}
BHV::BHV(const Triangle &obj) : storage(obj) {}
BHV::BHV(const Box &obj) : storage(obj) {}

//TODO : rework this, this is a mess
BHV::BHV(const BHV *one, const BHV *two, const BHV *three,
         const BHV *four)
    : leaf1(one), leaf2(two), leaf3(three), leaf4(four) {
    Box box1, box2;

    if (leaf1 != nullptr &&leaf2 != nullptr) {
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

BHV::~BHV() {}