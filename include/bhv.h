#pragma once
#include "structs.h"
#include "rtobject.h"
#include <memory>

#define BHV_LEAVES_NUMBER 4
// TODO : create leafnote
class BHV {
  private:
    std::shared_ptr<Box> storage;
    // TODO: make this into a vector
    std::shared_ptr<BHV> leaves[BHV_LEAVES_NUMBER] = {};

  public:
    //    BHV();
    BHV(std::shared_ptr<Sphere> obj);
    BHV(std::shared_ptr<Triangle> obj);
    BHV(std::shared_ptr<Box> obj); // this does not copy the box's content into it...
                         // though it could ?

    BHV(std::shared_ptr<BHV>one, std::shared_ptr<BHV>two = nullptr, std::shared_ptr<BHV>three = nullptr,
        std::shared_ptr<BHV>four = nullptr);

    Intersection intersectNodeBox(const Ray &ray) const;
    Intersection intersectSubNodes(const Ray &ray) const;
    std::shared_ptr<Box> getBox() const;

    ~BHV();
};