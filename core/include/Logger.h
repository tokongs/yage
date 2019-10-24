#pragma once

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace yage {
    
#define YAGE_LOG_LEVEL_TRACE 0
#define YAGE_LOG_LEVEL_DEBUG 1
#define YAGE_LOG_LEVEL_INFO 2
#define YAGE_LOG_LEVEL_WARN 3
#define YAGE_LOG_LEVEL_ERROR 4
#define YAGE_LOG_LEVEL_CRITICAL 5
#define YAGE_LOG_LEVEL_OFF 6
    
    class Logger {
    public:
        static void Init();

        static void SetLogLevel(int level);

        static std::shared_ptr<spdlog::logger> m_console_logger;
        static std::shared_ptr<spdlog::logger> m_file_logger;


#ifndef YAGE_NO_LOGGING
#define YAGE_TRACE(...) Logger::m_console_logger->trace(__VA_ARGS__); \
                        Logger::m_file_logger->trace(__VA_ARGS__);

#define YAGE_DEBUG(...) Logger::m_console_logger->debug(__VA_ARGS__); \
                        Logger::m_file_logger->debug(__VA_ARGS__);

#define YAGE_INFO(...) Logger::m_console_logger->info(__VA_ARGS__); \
                        Logger::m_file_logger->info(__VA_ARGS__);

#define YAGE_WARN(...) Logger::m_console_logger->warn(__VA_ARGS__); \
                        Logger::m_file_logger->warn(__VA_ARGS__);

#define YAGE_ERROR(...) Logger::m_console_logger->error(__VA_ARGS__); \
                        Logger::m_file_logger->error(__VA_ARGS__);

#define YAGE_CRITICAL(...) Logger::m_console_logger->critical(__VA_ARGS__); \
                            Logger::m_file_logger->critical(__VA_ARGS__); \

#else
#define YAGE_TRACE(__VA_ARGS__)
#define YAGE_INFO(__VA_ARGS__)
#define YAGE_DEBUG(__VA_ARGS__)
#define YAGE_ERROR(__VA_ARGS__)
#define YAGE_CRITICAL(__VA_ARGS__)
#endif
    };
}
