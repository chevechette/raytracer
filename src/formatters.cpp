#include "structs.h"

template <typename FormatContext>
auto fmt::formatter<Intersection>::format(const Intersection &intersect, FormatContext &ctx)
    -> decltype(ctx.out()) const {
    if (intersect) {
        return fmt::format_to(
            ctx.out(), "Intersection(Distance {}, Object {}, {})",
            intersect.dist, intersect.obj->to_string(), intersect.point);
    }
    return fmt::format_to(ctx.out(), "Intersection(invalid)");
}