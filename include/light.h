#pragma once
#include "structs.h"

enum LightType { Ambiant, Spot, Distant, None };

class Light {
  private:
    Color col;
    float lux = 1.0; // Lux power, could be an int or a 0-1 range.
    // If spot importnat, if sun, then this is a dir ? Complicated
    Coordinates posdir; // useless for ambiant

  protected:
    LightType ltype = LightType::None;

    double getLightDist(const Coordinates &point) const;
    Coordinates getLightDir(const Coordinates &point) const;

  public:
    Light(const Coordinates &posdir, const Color &col, float lux);
    Light(const Coordinates &posdir, const Color &col);
    ~Light();

    void setColor(const Color &color);
    void setLux(float luxpower);
    void setCoordinates(const Coordinates &pos);

    Color getColor() const;
    Color getLuxedColor() const; // this could be automatised.
    float getLux() const;
    LightType getType() const;
    // returns a normalised vector towards the light
    // The distance is annoying because you need to do the normalisation twice,
    // inneficient
    virtual bool illuminate(const Coordinates &from) const = 0;
};

class AmbiantLight : protected Light {
  public:
    bool illuminate(const Coordinates &from) const;
};

class SpotLight : protected Light {};

class DistantLight : public Light {
  protected:
    LightType ltype = LightType::Distant;

  public:
    DistantLight(const Coordinates &posdir, const Color &col, float lux);
    DistantLight(const Coordinates &posdir, const Color &col);
    ~DistantLight();
    bool illuminate(const Coordinates &from) const;
};