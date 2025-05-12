#pragma once

#include "opengl_include.h"
#include "render.h"
#include <memory> // shared_ptr usage
#include <vector>

class Singleton
{
private:
  Singleton() { };

public:
  Singleton& Get()
  {
    static Singleton the_singleton;
    return the_singleton;
  }
};

// TODO : throw errors EVERYWHERE
class GUIManager {
  // private:
  //   static GUIManager *instance; // TODO switch for shared ptr for thread safety
  
  public: // TODO: TMP SHIT
    Render background;
    GLFWwindow *window;
    bool  loaded = false;

  private:
    // static std::shared_ptr<GUIManager>   instance;
    // to do rework instance mecanism once i'm done with the rest

    GUIManager(const GUIManager &) = delete;
    GUIManager &operator=(const GUIManager &) = delete;

    GUIManager();
    ~GUIManager();

  public:
    static GUIManager &getInstance();
    static void release();

    // event shit
    static void glfwErrorCallback(int error, const char *description);
    static void guiKeyCallback(GLFWwindow *window, int key, int scancode,
                               int action, int mods);
    static void guiResizeCallback(GLFWwindow* window, int width, int height);

    void guiVarSetUp(); // TODO : rename
    void load();         // TODO rename these loading functions
    void unloadWindow();
    void unload();
    void mainloop();

    void renderGUI();
    void renderRaytracer();
    // void render

    // event ?

    // render options (full or partial to quick render)
    void renderBackground();
    // launch the rendering
    void renderFromCamera();

    // bool isloaded() const; ?
};
