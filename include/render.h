#pragma once

#include <vector>
#include "renderbufferpixelproxy.h"

class Render
{
private:
    int width;
    int height;

public: // TODO : TMP
    std::vector<unsigned char> buffer;

    // other GL variables

public:
    Render(int w, int h);
    ~Render();

    void adjustRenderSize(int w, int h);
    int getWidth();
    int getHeight();

    void renderPoint(int x, int y, Color col);
    RenderBufferPixelProxy operator[](int i);

    void renderBackgroundSin();
};