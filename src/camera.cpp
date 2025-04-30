// later upgrade
// multiple cameras, swtich
// adjustable cameras according to gui

#include "structs.h"

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
        Coordinates setDirection() const;

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

Coordinates     Camera::getPosition() const {
    return this->position;
}

// default light is a sunlike thing
// to do after the intersection of all the things
class Light {

};

// then ligh shout be like a spot light.