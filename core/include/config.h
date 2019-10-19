#pragma once

#define ROOT_DIR "/home/tokongs/projects/yage/"
#define LINUX
#define DEBUG

#define POSITION_BUFFER_INDEX 0
#define NORMAL_BUFFER_INDEX 1
#define COLOR_BUFFER_INDEX 2
#define TEX_COORD_BUFFER_INDEX 3
#define BONE_ID_BUFFER_INDEX 4
#define BONE_WEIGHT_BUFFER_INDEX 5
#ifdef DEBUG
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#define DECLARE_LOGGERS                                    \
    static std::shared_ptr<spdlog::logger> console_logger; \
    static std::shared_ptr<spdlog::logger> file_logger;

#define DEFINE_LOGGERS(className)                                     \
    std::shared_ptr<spdlog::logger> className::console_logger = NULL; \
    std::shared_ptr<spdlog::logger> className::file_logger = NULL;

#define INIT_LOGGERS(className)                                                                                                     \
    if (!className::console_logger)                                                                                                 \
        className::console_logger = spdlog::stdout_color_mt(std::string(#className) + std::string("_console_logger"));              \
    className::console_logger->flush_on(spdlog::level::err);                                                                        \
    if (!className::file_logger)                                                                                                    \
        try                                                                                                                         \
        {                                                                                                                           \
            className::file_logger = spdlog::basic_logger_mt(std::string(#className) + std::string("_file_logger"), "default.txt"); \
        className:                                                                                                                  \
            file_logger->flush_on(spdlog::level::err);                                                                              \
        }                                                                                                                           \
        catch (const spdlog::spdlog_ex &ex)                                                                                         \
        {                                                                                                                           \
            std::cout << "Failed to start window logger: " << ex.what() << std::endl;                                               \
        }
#define FILE_LOGGER(class, type, message)                        \
    if (#type == "error")                                        \
        class::file_logger->type("{}:{}:", __FILE__, __LINE__); \
    class::file_logger->type(message);

#define CONSOLE_LOGGER(class, type, message)                        \
    if (#type == "error")                                           \
        class::console_logger->type("{}:{}:", __FILE__, __LINE__); \
    class::console_logger->type(message);
#define LOG(class, type, message) FILE_LOGGER(class, type, message) CONSOLE_LOGGER(class, type, message)
#define FLUSH_LOGGERS(class) class::console_logger->flush(); class::file_logger->flush();
#else
#define DECLARE_LOGGERS
#define DEFINE_LOGGERS
#define INIT_LOGGERS
#define FILE_LOGGER(type, message)
#define CONSOLE_LOGGER(type, message)
#endif
