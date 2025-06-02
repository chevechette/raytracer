
#include <cstddef>
#include <stdexcept>

#include "graphic_presets.h" // Temporary import the
#include "messages.h"
#include "ray.h"
#include "structs.h"


// There is no actuall camera rotation, up is always up
// How do fisheye work anyway ? I remember doing that

class Camera {
  private:
    Coordinates position;
    Coordinates direction;
    float fov = FIELD_DEPTH;
    // not accurate,
    // TODO: update to a lenlike
    // calculation later
    std::size_t height = GRAPHIC_PRESET_GUI_HEIGHT;
    std::size_t width = GRAPHIC_PRESET_GUI_WIDTH;
    // TODO add POV distance
  public:
    Camera();

    Camera(const Coordinates &pos, const Coordinates &dir);
    ~Camera();

    void setPosition(Coordinates pos);
    void setDirection(Coordinates vec);
    void setScreenSize(std::size_t width, std::size_t height);

    Coordinates getPosition() const;
    Coordinates getDirection() const;

    Coordinates &getPositionRef();
    Coordinates &getDirectionRef();

    Ray createRay(std::size_t x, std::size_t y);
    // CreateRay...

    // TODO : Launch ray within the window parameter
};