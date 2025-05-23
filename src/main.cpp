
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
// TODO : Find C++ 23 tutorial to update
// TODO : CUDA upgrade for raytracing

// TODO : make a rendering point fucntion
// make a set of rendering functions


// TODO : Upgrade the error handling to exceptions
// TODO : CHECK ALL CONST !!

// Catching events 
void glfwErrorCallback(int error, const char* description) {
    fmt::println(stderr, "GLFW Err code {} : {}", error, description);
}

// UI events
static void guiKeyCallback(
    GLFWwindow* window, int key, int scancode, int action, int mods) {
    //TODO : set up all one key triggers
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        fmt::println(stdout, "GO THERE\n");

    }
}

// Library load and unload
void glfwSetUp() {
    // TODO : Upgrade Error handling 
    glfwSetErrorCallback(glfwErrorCallback);
    
    //TODO : set the GLFW_CONTEXT variables to request a specifc version of openGL 4.1 here
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //document yourself on those two set ups
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void imguiSetUp() {

    IMGUI_CHECKVERSION(); // TODO : Check what does this do ?
    ImGui::CreateContext();
}

int librarySetUp() {
    std::srand(std::time({}));
    if (!glfwInit())
        return EXIT_FAILURE;
    glfwSetUp(); // Includes OpenGL
    imguiSetUp();
    
    // Maybe set up the window creation here ?
    return EXIT_SUCCESS;
}

void librarySetDown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

//TODO verbose messagibg
//TODO logging correctly
int main(int argc, char* argv[]) {
    /// TODO : write all disclaimer and starting information
    fmt::print(stdout, "{} Version {}.{}\n", argv[0], RAYTRACER_VERSION_MAJOR, RAYTRACER_VERSION_MINOR);

    if (librarySetUp() != EXIT_SUCCESS)
        return EXIT_FAILURE;

    // TODO : SET UP VARIABLES window parameters
    GLFWwindow* window = glfwCreateWindow(
        GRAPHIC_PRESET_GUI_WIDTH,
        GRAPHIC_PRESET_GUI_HEIGHT,
        GRAPHIC_PRESET_GUI_NAME, nullptr, nullptr);

    if (!window) {
        // TODO : error handling
        librarySetDown();
        return EXIT_FAILURE;
    }

    Renderer    renderer = Renderer();

    if (!renderer.loadWindow(window)) {
        librarySetDown();
        return EXIT_FAILURE;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true); // true ports all glfw triggers to ImGUI 
    ImGui_ImplOpenGL3_Init(); // Can specify some version here


    // // Try to call some OpenGL functions, and print some more version info.
    // printf( "Renderer: %s.\n", glGetString( GL_RENDERER ) );
    // printf( "OpenGL version supported %s.\n", glGetString( GL_VERSION ) );
  
    // /* OTHER STUFF GOES HERE NEXT */

    // glfw parameterts setting up
    glfwSwapInterval(1);
    glfwSetKeyCallback(renderer.getWindow(), guiKeyCallback);
    // 9) In your application's input logic: you can poll
    // ImGui::GetIO().WantCaptureMouse/WantCaptureKeyboard
    // to check if Dear ImGui wants to obstruct mouse/keyboard
    // inputs from underlying apps.
    // e.g. when hovering a window WantCaptureMouse will be set to true,
    // one possible strategy would be to stop passing mouse events to your main application.

    // Temporary setting up  variables for GUI testing
    int     sliderSamplePP = 100;
    float   sliderMaxBouncDepth = 100;
    int     lastRenderTime = 0;
    int     backgroundColor = 0;
    bool    renderButtonClicked = false;
    bool    debug = false;


    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


    while (!glfwWindowShouldClose(renderer.getWindow())) {
        //Clear
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

        //  Poll events
        glfwPollEvents(); // Can be changed for  glfwWaitEvents ?
        // BOTH NEED TO BE HERE. I am unsure if order is important.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Add MORE rendering there
        renderer.render();
    }
    renderer.unloadWindow();

    librarySetDown();
    return EXIT_SUCCESS;
}