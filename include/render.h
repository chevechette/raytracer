#pragma once
// #pragma clang diagnostic ignored "-Wc++23-extensions"

#include "renderbufferpixelproxy.h"
#include <cstddef> // size_t
#include <vector>

class Render {
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
    RenderBufferPixelProxy operator[](std::size_t i);
    RenderBufferPixelProxy operator[](std::size_t x,
                                      std::size_t y); // Only works in c++23

    void renderBackgroundSin();
};