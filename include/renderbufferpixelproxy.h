#pragma once

#include "structs.h"

class RenderBufferPixelProxy { // assuming format GL_RGBA
  private:
    unsigned char &r;
    unsigned char &g;
    unsigned char &b;
    unsigned char &a;

  public:
    RenderBufferPixelProxy(unsigned char &r, unsigned char &g, unsigned char &b,
                           unsigned char &a);
    ~RenderBufferPixelProxy();

    RenderBufferPixelProxy &operator=(const RenderBufferPixelProxy &pix);
    RenderBufferPixelProxy &operator=(const Color &col);
};

// class RenderBufferRowProxy { // assuming format GL_RGBA
//     private :
//     public :
//         RenderBufferRowProxy() {}
//         ~RenderBufferRowProxy() {}

// };