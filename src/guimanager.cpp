

#include <iostream>
// Faster printing and formating
#include <fmt/core.h>
// For stderr and faster better printing
#include <cstdio>
#include <ctime>

#include "opengl_include.h"

#include <cmath>
#include <vector>
// TODO : Extension loader library to then make it compatible with different GPU
// library
#include "forward_declaration.h"
#include "graphic_presets.h"
#include "main.h"
#include "messages.h"
#include "ray.h"
#include "rtobject.h"
#include "structs.h"
#include "version_config.h"
#include <cmath>
#include <exception>
#include <vector>

// TOCO : Clean up the includes, this is a mess

// TODO : Relocate what can be from render to GUIManager
// TODO : Setup a list of cameras with appropriate GUI
// TODO : For each camera, create the parameters
// TODO : Go update the camera functions
// TODO : (static) add a few objects at a specific distance
// TODO : incorporate libraries initialisation into GUIManger
// TODO : Object manager with lists of obj
// TODO : Objectmanager with a binary tree (could be another class of obj leaf)
// TODO : Error throwing in all classes
// TODO : Error throwing from GUI Manager
// TODO : Check the unloads and memory leaks

// This could have been inheritance but I see no logical connection
// and never want to bother with mixing those two nor bother with casting
#include "managers.h"
#include "render.h"

// void renderBackground();
// void renderRaytracer();
// void renderGUI();

GUIManager::GUIManager()
    : window(nullptr),
      background(GRAPHIC_PRESET_GUI_WIDTH, GRAPHIC_PRESET_GUI_HEIGHT),
      cams(Camera(), Camera(), Camera()) {
    background.renderBackgroundSin();
}

GUIManager::~GUIManager() {
    if (this->loaded) {
        this->unload();
    }
}

GUIManager &GUIManager::getInstance() {
    static GUIManager instance = GUIManager();

    return instance;
}

void GUIManager::release() {
    // TODO: add unload if already init
    // GUIManager &instance::
    // if (GUIManager::get)
    // if (GUIManager::instance != nullptr) {
    //     delete GUIManager::instance;
    //     GUIManager::instance = nullptr;
    // }
}

void GUIManager::glfwErrorCallback(int error, const char *description) {
    fmt::println(stderr, "GLFW Err code {} : {}", error, description);
}

void GUIManager::guiKeyCallback(GLFWwindow *window, int key, int scancode,
                                int action, int mods) {
    // TODO : set up all one key triggers
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        fmt::println(stdout, "GO THERE\n");
    }
}

void GUIManager::guiResizeCallback(GLFWwindow *window, int width, int height) {
    GUIManager &gui = GUIManager::getInstance();

    gui.background.adjustRenderSize(
        width, height); // should I keep it if it is bigger ?
    gui.background.renderBackgroundSin();
}

void GUIManager::guiVarSetUp() {
    // TODO : Change it to set up the variables kept in memory for GUI setup

    // int     sliderSamplePP = 100;
    // float   sliderMaxBouncDepth = 100;
    // int     lastRenderTime = 0;
    // int     backgroundColor = 0;
    // bool    renderButtonClicked = false;
    // bool    debug = false;

    // GLuint textureID; // is this lost ?
    // glGenTextures(1, &textureID);
    // glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA,
    // GL_UNSIGNED_BYTE, nullptr);
}

// exception safe unloading before throwing
void GUIManager::load() {
    // TODO : Clean up later
    std::srand(std::time({})); // TODO : check if randomness is used
    if (!glfwInit()) {
        throw std::runtime_error(RT_MESSAGE_ERR_LIBRARY_GUI);
    }

    // TODO : Upgrade Error handling
    glfwSetErrorCallback(
        GUIManager::glfwErrorCallback); // TODO should be changed for other
                                        // repository of functions ?

    // TODO : set the GLFW_CONTEXT variables to request a specifc version of
    // openGL 4.1 here
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // document yourself on those two set ups
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    IMGUI_CHECKVERSION(); // TODO : Check what does this do ?
    ImGui::CreateContext();

    // TODO : SET UP VARIABLES window parameters
    this->window =
        glfwCreateWindow(GRAPHIC_PRESET_GUI_WIDTH, GRAPHIC_PRESET_GUI_HEIGHT,
                         GRAPHIC_PRESET_GUI_NAME, nullptr, nullptr);
    if (!window) {
        this->unload();
        throw std::runtime_error(RT_MESSAGE_ERR_LIBRARY_GUI_WINDOW);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        this->unload(); // unload contains conditional unloadwindow
        throw std::runtime_error(RT_MESSAGE_ERR_LIBRARY_GUI);
        // Handle initialization error
    }

    ImGui_ImplGlfw_InitForOpenGL(this->window,
                                 true); // true ports all glfw triggers to ImGUI
    ImGui_ImplOpenGL3_Init();           // Can specify some version here

    // // Try to call some OpenGL functions, and print some more version info.
    // printf( "Renderer: %s.\n", glGetString( GL_RENDERER ) );
    // printf( "OpenGL version supported %s.\n", glGetString( GL_VERSION ) );

    // refresh and swapping setting up, actually should the swap really be that
    // much updated when we are working with a ray tracer ?
    //  TODO : for readability, should move event stuff into their own function
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->window, GUIManager::guiKeyCallback);
    glfwSetWindowSizeCallback(this->window, GUIManager::guiResizeCallback);
    this->loaded = true;

    // 9) In your application's input logic: you can poll
    // ImGui::GetIO().WantCaptureMouse/WantCaptureKeyboard
    // to check if Dear ImGui wants to obstruct mouse/keyboard
    // inputs from underlying apps.
    // e.g. when hovering a window WantCaptureMouse will be set to true,
    // one possible strategy would be to stop passing mouse events to your main
    // application.
}
// called by the unload
void GUIManager::unloadWindow() {
    if (this->window && this->window != nullptr) {
        glfwDestroyWindow(this->window);
        this->window = nullptr;
    }
}

void GUIManager::unload() {
    if (this->loaded == false)
        return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    this->unloadWindow();
    ImGui::DestroyContext();
    glfwTerminate();
    this->loaded = false;
}

void GUIManager::mainloop() {
    // TODO : exception handling
    // TODO :  add check to make sure everything is loaded up before hand
    while (!glfwWindowShouldClose(this->window)) {
        // Clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //  Poll events
        glfwPollEvents(); // Can be changed for  glfwWaitEvents ?
        // BOTH NEED TO BE HERE. I am unsure if order is important.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Add MORE rendering there
        renderBackground();
        renderRaytracer();
        renderGUI();

        // Careful to avoid conflicts here
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(this->window);
    }
}

#include <iostream>
// TODO : Complete rework
void GUIManager::renderFromCamera(int cameraNo) {
    Camera &camera = this->cams[cameraNo]; // Does this need to be init here ?

    const int imgHeight = this->background.getHeight();
    const int imgWidth = this->background.getWidth();

    ObjectManager &objmanager = ObjectManager::getInstance();
    //     Render(main_viewport->Size.x,
    //            main_viewport->Size.y);
    for (int i = 0; i < imgWidth; i++) {
        for (int j = 0; j < imgHeight; j++) {
            try {
                // int i = GRAPHIC_PRESET_GUI_WIDTH / 2;
                // int j = GRAPHIC_PRESET_GUI_HEIGHT / 2;
                Ray pixRay = camera.createRay(i, j);

                Intersection intersect = objmanager.intersectAllObjects(pixRay);

                if (intersect) {
                    // std::cout << "Object found !" << std::endl;
                    this->background[i, j] = Color::fromHex(0xC34FFF);
                } else {
                    this->background[i, j] = Color::fromHex(0x40102F);
                }
                // std::cout << "STAP" << std::endl;
            } catch (std::exception &) {

                std::cout << "failwith " << i << j << std::endl;
            }
        }
    }
    // const ImGuiViewport*    main_viewport = ImGui::GetMainViewport();
}

// To port within the class
void GUIManager::renderBackground() {
    const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
    if (main_viewport == NULL || main_viewport == nullptr) {
        // throw exception ?
        return;
    }

    // Render bckgrnd =
    //     Render(main_viewport->Size.x,
    //            main_viewport->Size.y); // TODO : make this into
    //            property
    // bckgrnd.renderBackgroundSin();

    GLuint g_TextureID = 0;
    glGenTextures(1, &g_TextureID);
    glBindTexture(GL_TEXTURE_2D, g_TextureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->background.getWidth(),
                 this->background.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 this->background.buffer.data());

    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImVec2 viewportSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(viewportSize);
    ImGui::SetItemAllowOverlap();

    ImGui::Begin("Window With Background", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);

    // // Get current window size
    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    // // Display the image as background (filling the entire window)
    ImGui::Image((ImTextureID)g_TextureID, windowSize);
    ImGui::End();
}

// Can be a method within the class...
void GUIManager::renderGUI() {
    // TODO : add custom colors and design ? Not a priority

    const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(
        ImVec2(main_viewport->WorkPos.x + 15, main_viewport->WorkPos.y + 15));
    ImGui::SetNextWindowSize(
        ImVec2(main_viewport->Size.x * 0.30, main_viewport->Size.y * 0.90));

    if (ImGui::Begin("Render Menu")) {
        // TODO: CAMERA GUI
        static int currentCamera = 0;

        const char *cameras[] = {"Camera 1", "Camera 2", "Secret Cam 3"};
        ImGui::Combo("selected", &currentCamera, cameras,
                     IM_ARRAYSIZE(cameras)); // if var 1 set to 0, sHIT

        // TODO: check the decapsulation and find alternatives
        Camera &selectedCam = this->cams[currentCamera];
        Coordinates &pos = selectedCam.getPositionRef();
        Coordinates &dir = selectedCam.getDirectionRef();
        ImGui::DragFloat("X position", &pos.x, 0.1f, 0.0f, 0.0f, "%.06f");
        ImGui::DragFloat("Y position", &pos.y, 0.1f, 0.0f, 0.0f, "%.06f");
        ImGui::DragFloat("Z position", &pos.z, 0.1f, 0.0f, 0.0f, "%.06f");

        ImGui::DragFloat("X angle", &dir.x, 0.01f, 0.0f, 0.0f, "%.06f");
        ImGui::DragFloat("Y angle", &dir.y, 0.01f, 0.0f, 0.0f, "%.06f");
        ImGui::DragFloat("Z angle", &dir.z, 0.01f, 0.0f, 0.0f, "%.06f");

        // Select Camera
        // Cordinates x, y. z
        // Direction x, y, z
        // Rotation // not working
        // Render from cam

        //     ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        if (ImGui::Button("Render")) {
            this->renderFromCamera(currentCamera);
            // triggers calculation
        }
        if (ImGui::CollapsingHeader("Background settings")) {
            ImGui::Text("Parameters");
        }
    }
    ImGui::End();
}

void GUIManager::renderRaytracer() {
    GUIManager &guiinstance = GUIManager::getInstance();
    guiinstance.renderFromCamera(0);
}
