#pragma once

#include <memory> // shared_ptr usage
#include <vector>
#include "opengl_include.h"

//TODO : throw errors EVERYWHERE
class GUIManager {
    private:
        static  GUIManager   *instance; // TODO switch for shared ptr for thread safety
        // static std::shared_ptr<GUIManager>   instance;
        // to do rework instance mecanism once i'm done with the rest

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
            // TODO : add unload if already init
            if (GUIManager::instance != nullptr) {
                delete GUIManager::instance;
                GUIManager::instance = nullptr;
            }
        }

        //event shit
        static void glfwErrorCallback(int error, const char* description);
        static void guiKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        void guiVarSetUp(); // TODO : rename
        int load(); // TODO rename these loading functions
        void unloadWindow();
        void unload();
        void mainloop();

        //event ?

        //render options (full or partial to quick render)
        void    renderBackground();
        // launch the rendering
        void    renderFromCamera();
};
