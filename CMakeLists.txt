cmake_minimum_required(VERSION 3.22)

project(HelloRaytracer VERSION 0.0.1)

if(EXISTS "/usr/bin/gcc-13" AND EXISTS "/usr/bin/g++-13") 
    set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
endif()

# Compiler settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Diagnostic output to understand compiler details
message(STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Compiler Path: ${CMAKE_CXX_COMPILER}")


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
        message(FATAL_ERROR "GCC 13.0 or higher is required")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16.0)
        message(FATAL_ERROR "Clang 16.0 or higher is required")
    endif()
endif()

# Include directories
set(HEADERS include)

# Header generation
configure_file(${HEADERS}/version_config.h.in ${HEADERS}/version_config.h)

# Find required packages
find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS math)

# Source files
file(GLOB SRCS_FILES
        "src/*.cpp") #To use wildcards
# set(SRCS src/*.cpp)

# Create executable target
add_executable(helloraytracer ${SRCS_FILES})

# Configure target
target_include_directories(helloraytracer 
    PUBLIC ${HEADERS}
)

target_link_libraries(helloraytracer PRIVATE 
    fmt::fmt 
    glfw
    glad::glad
    OpenGL::GL
    imgui::imgui
    Boost::math
)