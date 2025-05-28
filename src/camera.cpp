// later upgrade
// multiple cameras, swtich
// adjustable cameras according to gui
#include "camera.h"

// TODO : update the create pixel for faning out the screen vectors
Camera::Camera()
    : position(
          Coordinates{CAMERA_DEFAULT_X, CAMERA_DEFAULT_Y, CAMERA_DEFAULT_Z}),
      direction(Coordinates{CAMERA_DIR_DEFAULT_X, CAMERA_DIR_DEFAULT_Y,
                            CAMERA_DIR_DEFAULT_Z}) {}

Camera::Camera(const Coordinates &pos, const Coordinates &dir)
    : position{pos}, direction{dir.normalize()} {}

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

#include <cmath> // is boost faster ? I heard not
#include <fmt/core.h>
#include <iostream>
Ray Camera::createRay(std::size_t x, std::size_t y) {
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        throw std::out_of_range(RT_MESSAGE_ERR_PIXEL_OOB);
    this->direction.normalizeSelf();



    Coordinates p = Coordinates{x - this->width / 2.0f + 0.5f,
                                (this->height / 2.0f - y + 0.5f), 1};


    double aspect_ratio = static_cast<double>(this->width) / this->height;
    double fov_radians = (100 * M_PI / 180.0);  // TODO: dehardcode the fov
    double fov_scale = std::tan(fov_radians * 0.5);

    p.x = (2.0 * (x + 0.5) / this->width - 1.0) * aspect_ratio;
    p.y = (1.0 - 2.0 * (y + 0.5) / this->height);

    
    // if (x == 0 && y == 0) {

    //     fmt::print(stdout, "Pixel world position: {} {} {}\n", p.x,
    //                p.y, p.z);
    // }
    p.normalizeSelf();
    p = p * fov_scale;


    Coordinates a = Coordinates{0, 0, 1} ^ this->direction;
    a.normalizeSelf();
    // angle of rotation
    double theta = std::acos(this->direction.z);
    float c =
        1 - std::cos(theta); // has to be normalized beforehand in constructor
    float s = std::sin(theta);

    // this can be simplified by removing the last column but is for future
    // reference
    Coordinates rotateCol1 =
        Coordinates{1 - c * a.y * a.y, c * a.x * a.y, -s * a.y};
    Coordinates rotateCol2 =
        Coordinates{c * a.x * a.y, 1 - c * a.x * a.x, s * a.x};
    Coordinates rotateCol3 =
        Coordinates{s * a.y, -s * a.x, 1 - c * (a.y * a.y + a.x * a.x)};

    Coordinates pixelPosition = {p * rotateCol1, p * rotateCol2,
                                 p * rotateCol3};

    float viewPlaneDistance = 1.00f;
    // Placeholder return
    pixelPosition = pixelPosition + ((this->direction * viewPlaneDistance)) +
                    this->position; 
    Coordinates rayPosition = this->position; // pixelPosition;
    Coordinates rayDirection = pixelPosition - this->position;
    rayDirection.normalizeSelf();
    Ray ray = Ray(rayPosition, rayDirection);
    return ray;
}

// default light is a sunlike thing
// to do after the intersection of all the things
class Light {};

// then ligh shout be like a spot light.