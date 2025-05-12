#pragma once
#include <vector>
#include <memory> // shared_ptr usage

#include "opengl_include.h"
#include "render.h"
#include "ray.h"

// TODO: Add camera storage, link them with GUI ?
class ObjectManager {

  public:                                      // TMP PUBLIC VARIABLES
                                               // would be the full libraries
    std::vector<std::shared_ptr<Object>> objs; // shared pointer ? optional ?

  private:
    ObjectManager(const ObjectManager &) = delete;
    ObjectManager &operator=(const ObjectManager &) = delete;

    ObjectManager();

    ~ObjectManager();

  public:
    static ObjectManager &getInstance();

    static void release();
    // remove(); // pop
    // binary tree structure... later

    // cameras map for edition
    void addObject(std::shared_ptr<Object> obj);

    void removeObjects();

    void createSphere(Coordinates coord, float radius, Color col);
    // TODO: add other objs

    Intersection intersectAllObjects(const Ray &ray);

    // TODO: override some fmt for printability
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
