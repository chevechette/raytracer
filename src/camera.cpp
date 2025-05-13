// later upgrade
// multiple cameras, swtich
// adjustable cameras according to gui

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

Camera::Camera(Coordinates pos, Coordinates dir)
    : position{pos}, direction{dir.normalize()},
      projectedPos{pos + (dir.normalize() * (-fov))} {}

Camera::~Camera() {}

void Camera::setPosition(Coordinates pos) {
    this->position = pos;
}

void Camera::setDirection(Coordinates dir) {
    this->direction = dir;
    this->direction.normalize();
}

void Camera::setScreenSize(std::size_t width, std::size_t height) {
    this->width = (width >= 0) ? width : 0;
    this->height = (height >= 0) ? width : 0;
}

Coordinates Camera::getPosition() const {
    return this->position;
}

Coordinates Camera::getDirection() const {
    return this->direction;
}

Ray Camera::createRay(std::size_t x, std::size_t y) {
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        throw std::out_of_range(RT_MESSAGE_ERR_PIXEL_OOB);

    Coordinates camRefPixel =
        Coordinates{(x - this->width / 2.0f), (y - this->height / 2.0f), 0};
    Coordinates upVec = Coordinates{0, 1, 0};
    Coordinates horVec = upVec ^ this->direction;
    horVec.normalize();
    upVec = horVec ^ this->direction;
    upVec.normalize();

    Coordinates pixel =
        (horVec * camRefPixel.x) + (upVec * camRefPixel.y) + this->position;
    return Ray(this->projectedPos, pixel - this->projectedPos);
}

// default light is a sunlike thing
// to do after the intersection of all the things
class Light {};

// then ligh shout be like a spot light.