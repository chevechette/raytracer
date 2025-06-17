#pragma once
#include "rtobject.h"
#include "structs.h"
#include <fmt/format.h>
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
    BHV(std::shared_ptr<Box> obj); // this does not copy the box's content into
                                   // it... though it could ?

    BHV(std::shared_ptr<BHV> one, std::shared_ptr<BHV> two = nullptr,
        std::shared_ptr<BHV> three = nullptr,
        std::shared_ptr<BHV> four = nullptr);

        int countLeaves() const;

    Intersection intersectNodeBox(const Ray &ray) const;
    Intersection intersectSubNodes(const Ray &ray) const;
    std::shared_ptr<Box> getBox() const;

    ~BHV();
};

template <> struct fmt::formatter<BHV> {
    constexpr auto parse(fmt::format_parse_context &ctx)
        -> decltype(ctx.begin()) {
        return (ctx.end());
    }

    template <typename FormatContext>
    auto format(const BHV &node, FormatContext &ctx) const
        -> decltype(ctx.out()) {
          //TODO : fix possible segfault via to_string() implementation
        return fmt::format_to(ctx.out(), "Node({} containing {} leaves)",
                              node.getBox()->to_string(), node.countLeaves());
    }
};