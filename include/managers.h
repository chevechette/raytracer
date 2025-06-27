#pragma once
#include <memory> // shared_ptr usage
#include <vector>

#include "bhv.h"
#include "camera.h"
#include "forward_declaration.h"
#include "opengl_include.h"
#include "ray.h"
#include "render.h"

// TODO: Add camera storage, link them with GUI ?
class ObjectManager {

  public:                                      // TMP PUBLIC VARIABLES
                                               // would be the full libraries
    std::vector<std::shared_ptr<Object>> objs; // shared pointer ? optional ?
    std::vector<std::shared_ptr<Box>> boxes;
    std::vector<std::shared_ptr<Object>> infinityObjs;
    std::vector<std::shared_ptr<BHV>> nodes;
    std::shared_ptr<BHV> tree = nullptr;

  private:
    ObjectManager(const ObjectManager &) = delete;
    ObjectManager &operator=(const ObjectManager &) = delete;

    ObjectManager();

    ~ObjectManager();

  public:
    static ObjectManager &getInstance();

    static void release();

    // cameras map for edition
    void addObject(std::shared_ptr<Object> obj);
    // called for planes and such
    void addInfinityObject(std::shared_ptr<Object> obj);
    // binary tree structure... later
    void addBox(std::shared_ptr<Box> box);

    // remove(); // pop
    void removeObjects();
    void removeNodes();

    void buildNodes();
    void buildTree();

    std::shared_ptr<BHV>
    recursiveTreeBuid(std::vector<std::shared_ptr<BHV>> &currentNodes,
                      std::vector<std::shared_ptr<BHV>> &savedNodes);

    void createSphere(Coordinates coord, float radius, Color col);
    void createTriangle(Coordinates a, Coordinates b, Coordinates c, Color col);

    void createPlane(Coordinates o, Coordinates n, Color col);
    // TODO: add plane
    // TODO: add a group of objects
    // TODO: update object tree

    Intersection intersectAllObjects(const Ray &ray);
    Intersection treeWalk(const Ray &ray);

    // TODO: override some fmt for printability
};

// TODO : throw errors EVERYWHERE
class GUIManager {
  private:
    GLFWwindow *window;
    Render bckgrnds[3];
    bool loaded = false;
    int selectedCamera = 0; // No get/set as it is only interacted by GUI
                            // private:
    //   static GUIManager *instance; // TODO switch for shared ptr for thread
    //   safety

  public:           // TODO: TMP SHIT
    Camera cams[3]; // TODO: Make it into an array of 3 cameras for switching

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
    static void guiResizeCallback(GLFWwindow *window, int width, int height);

    void guiVarSetUp(); // TODO : rename
    void load();        // TODO rename these loading functions

    void loadSpdlog();
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
    void renderFromCamera(int cameraNo);

    // bool isloaded() const; ?
};
