#pragma once
#include "structs.h"

//Floating is like a floating ball of light (suntype)
//Spotlight directs like a cone its light
enum LightType { Ambiant, Spot, Distant, Floating, None };

class Light {
  private:
    Color col;
    float lux = 1.0; // Lux power, could be an int or a 0-1 range.
    // If spot importnat, if sun, then this is a dir ? Complicated
    
    protected:
    Coordinates posdir; // useless for ambiant
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

    Coordinates getCoordinates() const;
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
  protected:
    LightType ltype = LightType::Ambiant;

  public:
    AmbiantLight(const Color &col, float lux);
    AmbiantLight(const Color &col);
    ~AmbiantLight();
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

class FloatingLight : public Light {
  protected:
    LightType ltype = LightType::Floating;

  public:
    FloatingLight(const Coordinates &posdir, const Color &col, float lux);
    FloatingLight(const Coordinates &postdir,const Color &col);
    ~FloatingLight();
    bool illuminate(const Coordinates &from) const;
};