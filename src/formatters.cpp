#include "rtobject.h"
#include "structs.h"

// TODO: Move all formatters here

// TODO: note all exception throw
template <typename FormatContext>
auto fmt::formatter<Intersection>::format(const Intersection &intersect,
                                          FormatContext &ctx)
    -> decltype(ctx.out()) const {
    if (intersect) {
        return fmt::format_to(
            ctx.out(), "Intersection(Distance {}, Object {}, {})",
            intersect.dist, intersect.obj->to_string(), intersect.point);
    }
    return fmt::format_to(ctx.out(), "Intersection(invalid)");
}

// template <typename FormatContext>
// auto fmt::formatter<Coordinates>::format(const Coordinates &point,
//                                          FormatContext &ctx) const
//     -> decltype(ctx.out()) {
//     return fmt::format_to(ctx.out(), "Coordinates({}, {}, {})", point.x,
//                           point.y, point.z);
// }