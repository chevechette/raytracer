#include "structs.h"
enum LightType { Sun, Spot };

class Light {
  private:
    Color col;
    float lux; // Lux power, could be an int or a 0-1 range.
    Coordinates
        pos; // If spot importnat, if sun, then this is a dir ? Complicated

  protected:
  public:
    Light();
    ~Light();

    Coordinates calculateVector(Coordinates intersectPoint);
    void checkBarriers(); 
};

// Maybe should light be inherited into spot or sol or ambiant

