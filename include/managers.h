#pragma once

#include <vector>
#include "opengl_include.h"

//TODO : throw errors EVERYWHERE
class GUIManager {
    private:
        static  GUIManager   *instance;

        GUIManager(const GUIManager&) = delete;
        GUIManager   &operator=(const GUIManager&) = delete;
        
        GUIManager() : window(nullptr) {
        }

        ~GUIManager() {

        }

        // Temporary public
    public:
        GLFWwindow* window;

    public:
        static  GUIManager &getInstance() {
            if (GUIManager::instance == nullptr) {
                GUIManager::instance = new GUIManager();
        }
            return *GUIManager::instance;
        }

        static  void    release() {
            if (GUIManager::instance != nullptr) {
                delete GUIManager::instance;
                GUIManager::instance = nullptr;
            }
        }

        //event shit
        static void glfwErrorCallback(int error, const char* description);
        static void guiKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        int load(); // TODO rename these loading functions
        void unloadWindow();
        void unload();

        //event ?

        //render options (full or partial to quick render)
        // launch the rendering
        void    renderFromCamera();
};
