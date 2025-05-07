#ifndef RT_RENDERER_H
#define RT_RENDERER_H

#include "opengl_include.h"

class Renderer {
    private:
        GLFWwindow      *window;
    protected:
    public:
        Renderer();
        ~Renderer();

        // GLFW Window
        GLFWwindow  *getWindow();

        bool loadWindow(GLFWwindow *window);
        const bool    hasValidWindow();

        // OPENGL
        void setUpBackground();
        void updateBackground();

        // RENDER stuff
        void render();
};


#endif