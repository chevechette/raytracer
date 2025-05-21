// TODO : Extension loader library to then make it compatible with different GPU
// library
// TODO : Find C++ 23 tutorial to check if something should be updated
// TODO : Multithreading
// TODO : CUDA upgrade for ray
// TODO : convert to smart pointers when appropriate
// TODO : write all disclaimer and starting information into its own thing
// TODO : Upgrade the error handling to exceptions
// TODO : CHECK ALL CONST !! ALL REF !! THE MOST MEANEST COMPILAITON RULES
// TODO : verbose messaging
// TODO : logging correctly
// TODO : clean up this file
// TODO : add documentation
// TODO : check all header files for name harmonisation
// TODO : Recheck the exceptions to maybe derive a type

#include <exception>
#include <fmt/core.h> // For stderr and faster better printing
#include <iostream>   // Faster printing and formating

#include "main.h" // This is a co2 wasting that should fall into the abyss
#include "version_config.h" // Disclaimer and stuff should go there

#include "managers.h"

int main(int argc, char *argv[]) {
    fmt::print(stdout, "{} Version {}.{}\n", argv[0], RAYTRACER_VERSION_MAJOR,
               RAYTRACER_VERSION_MINOR);

    try {
        GUIManager &gui = GUIManager::getInstance();
        gui.load(); // if load failure, the load unloads what has been init so
                    // far

        gui.guiVarSetUp(); // TODO : Init the menu variables

        ObjectManager &objs = ObjectManager::getInstance();
        objs.createSphere(Coordinates{100, 100, 500}, 30.0, Color::random());
        // objs.createTriangle(Coordinates{-200, 0, 200}, Coordinates{200, 200, 200},
        //                     Coordinates{-200, -200, 200}, Color::random());

        gui.mainloop();
        gui.unload(); // SEGFAULT IF NOT UNLOADED
    } catch (const std::exception &) {
        // GUIManager::release(); // maybe release should be part withing the
        // inner throwing of the singleton thant to share_ptr
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}