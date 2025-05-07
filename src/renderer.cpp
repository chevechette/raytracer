
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

        // add(); // push
        // remove(); // pop
        // binary tree structure... later

        // cameras map for edition

        // 

};

class GUIManager {
    private:
        static  GUIManager   *instance;

        GUIManager(const ObjectManager&) = delete;
        GUIManager   &operator=(const ObjectManager&) = delete;
        
        GUIManager() {
        }

        ~GUIManager() {

        }

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

        //event ?

        //render options (full or partial to quick render)
        // launch the rendering

        void    renderFromCamera() {
            const ImGuiViewport*    main_viewport = ImGui::GetMainViewport();

            std::vector<int> objectList(0, 0);

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
};


// should be made a singleton

Renderer::Renderer() {
    this->window = nullptr;
}

Renderer::~Renderer() {
    this->unloadWindow();

}

GLFWwindow  *Renderer::getWindow() {
    return this->window;
}

bool Renderer::loadWindow(GLFWwindow *window) {
    if (!window) {
        return false; // TODO : error  handling
    }
    this->window = window;
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Handle initialization error
        this->unloadWindow();
        return false;
    }
    return true;
}

void Renderer::unloadWindow() {
    if (this->hasValidWindow()) {
        glfwDestroyWindow(window);
    }
    this->window = nullptr;
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

// Params : camera, pixel data coordinate, object
float    raycast() {
    // actually, this should return the distance
    return -1;
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

