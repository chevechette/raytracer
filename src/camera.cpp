// later upgrade
// multiple cameras, swtich
// adjustable cameras according to gui
#include "camera.h"

//TODO : update the create pixel for faning out the screen vectors
Camera::Camera()
    : position(
          Coordinates{CAMERA_DEFAULT_X, CAMERA_DEFAULT_Y, CAMERA_DEFAULT_Z}),
      direction(Coordinates{CAMERA_DIR_DEFAULT_X, CAMERA_DIR_DEFAULT_Y,
                            CAMERA_DIR_DEFAULT_Z}) {
          this->projectedPos =
              this->position + (this->direction.normalize() * (-fov));
}

Camera::Camera(const Coordinates &pos, const Coordinates &dir)
    : position{pos}, direction{dir.normalize()},
      projectedPos{pos + (dir.normalize() * (-fov))} {}

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
#include <iostream>
#include <fmt/core.h>
Ray Camera::createRay(std::size_t x, std::size_t y) {
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        throw std::out_of_range(RT_MESSAGE_ERR_PIXEL_OOB);

    Coordinates camRefPixel =
        Coordinates{(x - this->width / 2.0f), (y - this->height / 2.0f), 0};
    Coordinates upVec = Coordinates{0, 1, 0};
    Coordinates horVec = upVec ^ this->direction;
    upVec = horVec.normalizeSelf() ^ this->direction;
    upVec.normalizeSelf();

    // this deviates badly
    Coordinates pixel =
    (horVec * camRefPixel.x) + (upVec * camRefPixel.y) + this->position;
    
    Coordinates projectedPos = this->position + (this->direction.normalize() * (-5));
    projectedPos = projectedPos - pixel;
    projectedPos.normalizeSelf();
    // fix fisheye
    // fmt::print(stdout, "PIXEL {} {} {}\n", pixel.x, pixel.y, pixel.z);
    // fmt::print(stdout, "vector {} {} {}\n", projectedPos.x, projectedPos.y, projectedPos.z);
    // return Ray(pixel, this->direction);
    return Ray(this->position, projectedPos);
}

// default light is a sunlike thing
// to do after the intersection of all the things
class Light {};

// then ligh shout be like a spot light.