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
// Error throw check ok

#include "messages.h"
#include <exception>

#include "logger.h"
#include "main.h" // This is a co2 wasting that should fall into the abyss
#include "managers.h"
#include "version_config.h" // Disclaimer and stuff should go there

// TODO: Move this into a proper object funtion
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
    objs.createDistantLight(Coordinates{0, 0.5, 0.5}, Color{1, 1, 1, 1});

    objs.buildTree();
    spdlog::info("Tree has been built");
}

int main(int argc, char *argv[]) {
    try {
        // TODO : add some parsing method for argc, argv
        printLogStart(argc, argv);

        GUIManager &gui = GUIManager::getInstance();
        try {
            gui.load(); // if load failure, the load unloads what has been init
                        // so far
        } catch (const std::exception &e) {
            spdlog::critical("Something went wrong on library load !");
            throw e;
        }

        gui.guiVarSetUp(); // TODO : Init the menu variables
        objectListGeneration();

        gui.mainloop();
        gui.unload(); // SEGFAULT IF NOT UNLOADED -> should be handled by catch
    } catch (const std::exception &) {
        spdlog::critical("Critical error, we are out.");
        // GUIManager::release(); // maybe release should be part withing the
        // inner throwing of the singleton thant to share_ptr
        return EXIT_FAILURE;
    }
    spdlog::info("Successful exit");
    return EXIT_SUCCESS;
}