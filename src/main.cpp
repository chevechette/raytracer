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

#include <exception>

#include "logger.h"
#include "main.h" // This is a co2 wasting that should fall into the abyss
#include "managers.h"
#include "version_config.h" // Disclaimer and stuff should go there

void loggingSetup() {}

int main(int argc, char *argv[]) {
    try {
        auto consoleSink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto logfileSink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(LOG_FILE);

        // TODO : add an option to choose either one, or both sinks. Plus if
        // file gets overwritten or not
        auto defaultLogger = std::make_shared<spdlog::logger>(
            DEFAULT_LOGGER, spdlog::sinks_init_list{logfileSink, consoleSink});

        spdlog::register_logger(defaultLogger);
        spdlog::set_default_logger(defaultLogger);

        spdlog::set_level(spdlog::level::debug);
        spdlog::info("{} Version {}.{}\n", argv[0], RAYTRACER_VERSION_MAJOR,
                     RAYTRACER_VERSION_MINOR);

    } catch (const std::exception &) {
        // GUIManager::release(); // maybe release should be part withing the
        // inner throwing of the singleton thant to share_ptr
        std::cout << "This sucks" << std::endl;
        return EXIT_FAILURE;
    }
    // TODO: Export this into a default logger with a file

    try {
        GUIManager &gui = GUIManager::getInstance();
        gui.load(); // if load failure, the load unloads what has been init so
                    // far

        gui.guiVarSetUp(); // TODO : Init the menu variables

        ObjectManager &objs = ObjectManager::getInstance();
        objs.createSphere(Coordinates{0, 0, 10}, 5.0, Color::random());
        objs.createSphere(Coordinates{10, 15, 20}, 1.0, Color::random());
        objs.createSphere(Coordinates{-20, -20, 20}, 10.0, Color::random());
        objs.createTriangle(Coordinates{-20, 0, 20}, Coordinates{20, 20, 20},
                            Coordinates{-20, -20, 20}, Color::random());
        objs.createPlane(Coordinates{0, 3, 0}, Coordinates{0.5, 0.5, 0},
                         Color::random());

        objs.buildTree();

        gui.mainloop();
        gui.unload(); // SEGFAULT IF NOT UNLOADED
    } catch (const std::exception &) {
        // GUIManager::release(); // maybe release should be part withing the
        // inner throwing of the singleton thant to share_ptr
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}