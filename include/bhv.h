#pragma once
#include "rtobject.h"
#include <memory>

// TODO : create leafnote
class BHV {
  private:
    std::shared_ptr<Box> storage;
    // TODO: make this into a vector
    std::shared_ptr<BHV> leaf1 = nullptr;
    std::shared_ptr<BHV>leaf2 = nullptr;
    std::shared_ptr<BHV>leaf3 = nullptr;
    std::shared_ptr<BHV>leaf4 = nullptr;

  public:
    //    BHV();
    BHV(std::shared_ptr<Sphere> obj);
    BHV(std::shared_ptr<Triangle> obj);
    BHV(std::shared_ptr<Box> obj); // this does not copy the box's content into it...
                         // though it could ?

    BHV(std::shared_ptr<BHV>one, std::shared_ptr<BHV>two = nullptr, std::shared_ptr<BHV>three = nullptr,
        std::shared_ptr<BHV>four = nullptr);

    std::shared_ptr<Box> getBox() const;

    ~BHV();
};