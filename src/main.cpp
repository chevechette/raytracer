// TODO : Extension loader library to then make it compatible with different GPU
// library
// TODO : Find C++ 23 tutorial to check if something should be updated
// TODO : Multithreading
// TODO : CUDA upgrade for ray
// TODO : write all disclaimer and starting information into its own thing
// TODO : Upgrade the error handling to exceptions
// TODO : CHECK ALL CONST !! ALL REF !! THE MOST MEANEST COMPILAITON RULES
// TODO : verbose messaging
// TODO : clean up this file
// TODO : add documentation
// TODO : check all header files for name harmonisation
// TODO : Recheck the exceptions to maybe derive a type
// TODO : catch control C for exit
// TODO : Error throw check

#include "messages.h"
#include <exception>

#include "logger.h"
#include "main.h" // This is a co2 wasting that should fall into the abyss
#include "managers.h"
#include "version_config.h" // Disclaimer and stuff should go there

//TODO: Move this into a proper object funtion
void printLogStart(int argc, char *argv[]) {
    if (argc > 0)
        spdlog::info("{} Version {}.{}\n", argv[0], RAYTRACER_VERSION_MAJOR,
                     RAYTRACER_VERSION_MINOR);
}

void objectListGeneration() {

    ObjectManager &objs = ObjectManager::getInstance();
    objs.createSphere(Coordinates{0, 0, 10}, 5.0, Color::random());
    objs.createSphere(Coordinates{10, 15, 20}, 1.0, Color::random());
    objs.createSphere(Coordinates{-20, -20, 20}, 10.0, Color::random());
    objs.createTriangle(Coordinates{-20, 0, 20}, Coordinates{20, 20, 20},
                        Coordinates{-20, -20, 20}, Color::random());
    objs.createPlane(Coordinates{0, 3, 0}, Coordinates{0.5, 0.5, 0},
                     Color::random());

    objs.buildTree();
}

int main(int argc, char *argv[]) {
    // TODO: Export this into a default logger with a file
    try {
        GUIManager &gui = GUIManager::getInstance();
        gui.load(); // if load failure, the load unloads what has been init so
                    // far
        printLogStart(argc, argv);
        // TODO : add some parsing method for argc, argv
        gui.guiVarSetUp(); // TODO : Init the menu variables
        objectListGeneration();

        gui.mainloop();
        gui.unload(); // SEGFAULT IF NOT UNLOADED
    } catch (const std::exception &) {
        // GUIManager::release(); // maybe release should be part withing the
        // inner throwing of the singleton thant to share_ptr
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}