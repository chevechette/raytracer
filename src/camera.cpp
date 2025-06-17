// later upgrade
// multiple cameras, swtich
// adjustable cameras according to gui
#include "camera.h"

#include "logger.h"

#include <cmath> // is boost faster ? I heard not
// TODO : update the create pixel for faning out the screen vectors
Camera::Camera()
    : position(
          Coordinates{CAMERA_DEFAULT_X, CAMERA_DEFAULT_Y, CAMERA_DEFAULT_Z}),
      direction(Coordinates{CAMERA_DIR_DEFAULT_X, CAMERA_DIR_DEFAULT_Y,
                            CAMERA_DIR_DEFAULT_Z}) {}

Camera::Camera(const Coordinates &pos, const Coordinates &dir)
    : position{pos}, direction{dir.normalize()} {

    spdlog::info("Camera Ray direction initialized at {} {} {}", direction.x,
                 direction.y, direction.z);
}

Camera::~Camera() {}

void Camera::setPosition(Coordinates pos) {
    this->position = pos;
}

void Camera::setDirection(Coordinates dir) {
    this->direction = dir;
    this->direction.normalizeSelf();
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

Coordinates &Camera::getPositionRef() {
    return this->position;
}

Coordinates &Camera::getDirectionRef() {
    return this->direction;
}

Ray Camera::createRay(std::size_t x, std::size_t y) {
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        throw std::out_of_range(RT_MESSAGE_ERR_PIXEL_OOB);
    // this->direction.normalizeSelf();

    Coordinates p;

    p.x = 2.0f * (x + 0.5) / this->width - 1.0f;
    p.y = 1.0f - 2.0f * (y + 0.5) / this->height;
    p.z = 1;

    double aspect_ratio = static_cast<double>(this->width) / this->height;
    double fov_radians = (45 * M_PI / 180.0); // TODO: dehardcode the fov
    double fov_scale = std::tan(fov_radians / 2.0);
    double inv_fov = 1.0 / fov_scale;

    p.x *= aspect_ratio * fov_scale;
    p.y *= fov_scale;
    // p.z *= 1.0f;

    Coordinates pixelPosition = p;

    Coordinates a = Coordinates{0, 0, 1} ^ this->direction;
    // angle of rotation

    // if (a.abs() > 0.0001) {
    a.normalizeSelf();

    double theta = std::acos(Coordinates{0, 0, 1} * this->direction);
    pixelPosition = p * std::cos(theta) + (a ^ p) * sin(theta) +
                    a * (a * p) * (1 - std::cos(theta));

    // }
    Coordinates rayPosition = this->position;
    Coordinates rayDirection = pixelPosition;
    rayDirection.normalizeSelf();
    if (((x == 0 || x == width - 1) && (y == 0 || y == height - 1)) ||
        (x == width / 2 && y == height / 2)) {
        spdlog::debug("Ray direction at pixel {} {}: {}", x, y,
                   rayDirection);
    }
    Ray ray = Ray(rayPosition, rayDirection);
    return ray;
}

// default light is a sunlike thing
// to do after the intersection of all the things
class Light {};

// then ligh shout be like a spot light.