

#include <iostream>
// Faster printing and formating
#include <fmt/core.h>
// For stderr and faster better printing
#include <cstdio> 
#include <ctime>

#include "opengl_include.h"

#include <vector>
#include <cmath>
// TODO : Extension loader library to then make it compatible with different GPU library

#include "main.h"
#include "version_config.h"
#include "graphic_presets.h"


#include "renderer.h"

#include <vector>
#include <cmath>

#include "graphic_presets.h"
#include "structs.h"
#include "renderer.h"
#include "ray.h"


#include "forward_declaration.h"
#include "structs.h"
#include "object.h"

//TODO : Relocate what can be from render to GUIManager
//TODO : Setup a list of cameras with appropriate GUI
//TODO : For each camera, create the parameters
//TODO : Go update the camera functions
//TODO : (static) add a few objects at a specific distance
//TODO : incorporate libraries initialisation into GUIManger
//TODO : Object manager with lists of obj
//TODO : Objectmanager with a binary tree (could be another class of obj leaf)

// This could have been inheritance but I see no logical connection
// and never want to bother with mixing those two nor bother with casting

#include "managers.h"

class ObjectManager {
    private:
        static  ObjectManager   *instance;

        ObjectManager(const ObjectManager&) = delete;
        ObjectManager   &operator=(const ObjectManager&) = delete;
        
        ObjectManager() {
        }

        ~ObjectManager() {

        }

    public:
        static  ObjectManager &getInstance() {
            if (ObjectManager::instance == nullptr) {
                ObjectManager::instance == new ObjectManager();
        }
            return *ObjectManager::instance;
        }

        static  void    release() {
            if (ObjectManager::instance != nullptr) {
                delete ObjectManager::instance;
                ObjectManager::instance = nullptr;
            }
        }

        void    loadLibraries() {

        }

        void    unloadLibraries() {

        }

        // add(); // push
        // remove(); // pop
        // binary tree structure... later

        // cameras map for edition

        // 

};

void GUIManager::glfwErrorCallback(int error, const char* description) {
    fmt::println(stderr, "GLFW Err code {} : {}", error, description);
}


void GUIManager::guiKeyCallback(
    GLFWwindow* window, int key, int scancode, int action, int mods) {
    //TODO : set up all one key triggers
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        fmt::println(stdout, "GO THERE\n");

    }
}


int GUIManager::load() {
    
    std::srand(std::time({}));
    if (!glfwInit())
        return EXIT_FAILURE;
    
    // TODO : Upgrade Error handling 
    glfwSetErrorCallback(GUIManager::glfwErrorCallback); // TODO should be changed for other repository of functions ?
    
    //TODO : set the GLFW_CONTEXT variables to request a specifc version of openGL 4.1 here
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //document yourself on those two set ups
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    IMGUI_CHECKVERSION(); // TODO : Check what does this do ?
    ImGui::CreateContext();

    // TODO : SET UP VARIABLES window parameters
    this->window = glfwCreateWindow(
        GRAPHIC_PRESET_GUI_WIDTH,
        GRAPHIC_PRESET_GUI_HEIGHT,
        GRAPHIC_PRESET_GUI_NAME, nullptr, nullptr);
    if (!window) {
        this->unload();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Handle initialization error
        this->unloadWindow();
        return EXIT_FAILURE;
    }

    ImGui_ImplGlfw_InitForOpenGL(this->window, true); // true ports all glfw triggers to ImGUI 
    ImGui_ImplOpenGL3_Init(); // Can specify some version here

    return EXIT_SUCCESS;
}

void    GUIManager::unloadWindow() {

    if (this->window && this->window != nullptr) {
        glfwDestroyWindow(window);
        this->window = nullptr;
    }
}

void    GUIManager::unload() {
    this->unloadWindow();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    
}



void    GUIManager::renderFromCamera() {
    const ImGuiViewport*    main_viewport = ImGui::GetMainViewport();

    std::vector<int> objectList(0, 0); // should be up

    for (int i = 0; i < main_viewport->Size.x ; i++) {
        for (int j = 0; j < main_viewport->Size.y ; j++) {
            float dist = -1;
            for (auto elem : objectList) {
                // Test interesec
                // auto raydist = raycast();
                // if (dist == -1 || dist > raydist) {
                //     dist = raydist;
                //     // this should update some object reference
                //     //pixel[i, j] = object.color;
                // }
                // if (auto dist = raycast >=0) {
                // }

            }
        }
    }
}

// should be made a singleton

Renderer::Renderer() {
    this->window = nullptr;
}

Renderer::~Renderer() {
}

GLFWwindow  *Renderer::getWindow() {
    return this->window;
}

bool Renderer::loadWindow(GLFWwindow *window) {
    this->window = window;
    return true;
}

const bool    Renderer::hasValidWindow() {
    if (this->window && this->window != nullptr)
        return true;
    return false;
}

void Renderer::setUpBackground() {

}

void Renderer::updateBackground() {

}

// To port withing the class
void renderBackground() {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    std::vector<unsigned char> background(main_viewport->Size.x * main_viewport->Size.y * 4);

    for (int i = 0 ; i < main_viewport->Size.x * main_viewport->Size.y ; i++) {
        double colsin = (i / (main_viewport->Size.x) / 20.0) + (fmod(i,main_viewport->Size.x) / 20.0);
        colsin = std::fmod(colsin, 180.0);
        // fmt::println(colsin);
        background[i * 4] = 0xFF * (sin(colsin) * 0.5 + 0.5);
        background[i * 4 + 1] = 0xFF * (sin(colsin) * 0.5 + 0.5);
        background[i * 4 + 2] = 0xFF * (sin(colsin) * 0.5 + 0.5);
        background[i * 4 + 3] = 0xFF;
    }
    GLuint  g_TextureID = 0;

    
    glGenTextures(1, &g_TextureID);
    glBindTexture(GL_TEXTURE_2D, g_TextureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, main_viewport->Size.x, 
        main_viewport->Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, background.data());


    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    // ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImVec2 viewportSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(viewportSize);
    ImGui::Begin("Window With Background", nullptr, ImGuiWindowFlags_NoTitleBar);

    // // Get current window size
    ImVec2 windowSize = ImGui::GetContentRegionAvail();

    // // Display the image as background (filling the entire window)
    ImGui::Image((ImTextureID)g_TextureID, windowSize);
    ImGui::End();
}

// Can be a method within the class...
void renderGUI() {
    // TODO : add custom colors and design ? Not a priority

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 15, main_viewport->WorkPos.y + 15));
    ImGui::SetNextWindowSize(ImVec2(main_viewport->Size.x * 0.30, main_viewport->Size.y * 0.90));

    if (ImGui::Begin("Render Menu")) {
        //     ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        if (ImGui::Button("Render")) {
            // triggers calculation
        }
        if (ImGui::CollapsingHeader("Background settings")) {
            ImGui::Text("Parameters");
        }
    }
    ImGui::End();
}

void renderRaytracer() {
    GUIManager  &guiinstance = GUIManager::getInstance();
    guiinstance.renderFromCamera();
}


void Renderer::render() {
    renderBackground();
    renderRaytracer();
    renderGUI();

    // Careful to avoid conflicts here
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(this->getWindow());
}


GUIManager      *GUIManager::instance = nullptr;
ObjectManager   *ObjectManager::instance = nullptr;

