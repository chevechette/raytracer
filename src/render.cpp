#include <stdexcept>

#include "render.h" // class definiton
#include "messages.h"

Render::Render(int w, int h) : width(w), height(h), buffer(w * h * 4)
{
}

Render::~Render() {}

void Render::adjustRenderSize(int w, int h)
{
    this->width = w;
    this->height = h;
    this->buffer.resize(width * height * 4);
} // set width height will change buffer size..

int Render::getWidth()
{
    return this->width;
}
int Render::getHeight()
{
    return this->height;
}

void Render::renderPoint(int x, int y, Color col) {}

// TODO: implement a [][] operator
// maybe add a tuple for quick access ?
RenderBufferPixelProxy
Render::operator[](int i)
{
    if (i < 0 || i >= height * width)
    {
        // TODO : log this
        throw std::out_of_range(RT_MESSAGE_ERR_PIXEL_OOB);
    }
    return RenderBufferPixelProxy(this->buffer[i * 4], this->buffer[i * 4 + 1], this->buffer[i * 4 + 2], this->buffer[i * 4 + 3]);
}

void Render::renderBackgroundSin()
{
    for (int i = 0; i < this->width * this->height; i++)
    {
        double colsin = (i / (this->width) / 20.0) + (fmod(i, this->width) / 20.0);
        colsin = std::fmod(colsin, 180.0);
        // fmt::println(colsin);
        try
        {
            this->operator[](i) = Color{
                static_cast<float>(sin(colsin) * 0.5 + 0.5),
                static_cast<float>(sin(colsin) * 0.5 + 0.5),
                static_cast<float>(sin(colsin) * 0.5 + 0.5),
            };
        }
        catch (std::exception &)
        {
            continue;
        }
    }
}