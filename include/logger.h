#pragma once

//TODO: Make all error messages
//TODO: Translate all error messages
//TODO: Remake the error classes
//TODO: Check all error exception
//TODO: Send exception enverywhere
//TODO: Add basic logging messages initialisation
//TODO: Open log file
//TODO: Overwrite or appen to log file
//TODO: Some parameters handling -> Version print for the Raytracer, or print verbose
//TODO: Remove a lot of commentary\
//TODO: Update all todo lists
//TODO: Sort  messages by theme
//TODO: Keep count of all objects to check for memory leaks

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#define LOG_FILE            "logs/raytracer.log"
#define CONSOLE_LOGGER      "console"
#define FILE_LOGGER         "filelog"
#define DEFAULT_LOGGER      "default"

#include "messages.h"