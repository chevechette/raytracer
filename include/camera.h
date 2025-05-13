
#include <cstddef>
#include <stdexcept>

#include "graphic_presets.h" // Temporary import the
#include "messages.h"
#include "ray.h"
#include "structs.h"

#define FIELD_DEPTH 20.0;
#define VISION_ANGLE 80.0; // should this be in randiant ?

// There is no actuall camera rotation, up is always up
// How do fisheye work anyway ? I remember doing that

class Camera {
  private:
    Coordinates position;
    Coordinates direction;
    float fov = FIELD_DEPTH;
    Coordinates projectedPos;
    // not accurate,
    // TODO: update to a lenlike
    // calculation later
    std::size_t height = GRAPHIC_PRESET_GUI_HEIGHT;
    std::size_t width = GRAPHIC_PRESET_GUI_WIDTH;
    // TODO add POV distance
  public:
    Camera(Coordinates pos, Coordinates dir);
    ~Camera();

    void setPosition(Coordinates pos);
    void setDirection(Coordinates vec);
    void setScreenSize(std::size_t width, std::size_t height);

    Coordinates getPosition() const;
    Coordinates getDirection() const;

    Ray createRay(std::size_t x, std::size_t y);
    // CreateRay...

    // TODO : Launch ray within the window parameter
};