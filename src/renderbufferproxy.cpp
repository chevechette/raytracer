
#include "renderbufferpixelproxy.h"

//TODO: note all exception throw

RenderBufferPixelProxy::RenderBufferPixelProxy(unsigned char &r,
                                               unsigned char &g,
                                               unsigned char &b,
                                               unsigned char &a)
    : r(r), g(g), b(b), a(a) {}

RenderBufferPixelProxy::~RenderBufferPixelProxy() {}

RenderBufferPixelProxy &
RenderBufferPixelProxy::operator=(const RenderBufferPixelProxy &pix) {
    if (this == &pix)
        return *this;
    r = pix.r;
    g = pix.g;
    b = pix.b;
    a = pix.a;
    return *this;
}

RenderBufferPixelProxy &RenderBufferPixelProxy::operator=(const Color &col) {
    r = col.r * 0xFF;
    g = col.g * 0xFF;
    b = col.b * 0xFF;
    a = col.a * 0xFF;
    return *this;
}
