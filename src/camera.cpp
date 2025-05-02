// later upgrade
// multiple cameras, swtich
// adjustable cameras according to gui

#include "graphic_presets.h" // Temporary import the 
#include "structs.h"

#define FIELD_DEPTH     100.0;
#define VISION_ANGLE    80.0;

// How do fisheye work anyway ? I remember doing that

class Camera {
    private:
        Coordinates position;
        Coordinates direction;
        // TODO add POV distance
    public:
        Camera(Coordinates pos, Coordinates dir);
        ~Camera();

        void    setPosition(Coordinates pos);
        void    setDirection(Coordinates vec);
        Coordinates getPosition() const;
        Coordinates getDirection() const;

        //CreateRay...

        //TODO : Launch ray within the window parameter
};

Camera::Camera(Coordinates pos, Coordinates dir) :
position{pos}, direction{dir} {}

Camera::~Camera() {}

void    Camera::setPosition(Coordinates pos) {
    this->position = pos;
}

void    Camera::setDirection(Coordinates dir) {
    this->direction = dir;
}

Coordinates     Camera::getPosition() const {
    return this->position;
}

Coordinates     Camera::getDirection() const {
    return this->direction;
}

// default light is a sunlike thing
// to do after the intersection of all the things
class Light {

};

// then ligh shout be like a spot light.