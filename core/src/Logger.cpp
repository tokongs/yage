#include "Logger.h"

namespace yage {

    std::shared_ptr<spdlog::logger> Logger::m_console_logger = nullptr;
    std::shared_ptr<spdlog::logger> Logger::m_file_logger = nullptr;

    void Logger::Init() {
        m_console_logger = spdlog::stdout_color_mt("YAGE Console Logger");
        m_console_logger->flush_on(spdlog::level::err);

        try {
            m_file_logger = spdlog::basic_logger_mt(std::string("YAGE File LOGGER"), "LOG.txt");
            className:
            m_file_logger->flush_on(spdlog::level::err);
        }
        catch (const spdlog::spdlog_ex &ex) {
            m_file_logger->warn("Failed to init file logger");
        }

       SetLogLevel(YAGE_LOG_LEVEL_ERROR);
    }

    void Logger::SetLogLevel(int level) {
        switch (level) {
            case 1:
                m_console_logger->set_level(spdlog::level::trace);
                m_file_logger->set_level(spdlog::level::trace);
                break;
            case 2:
                m_console_logger->set_level(spdlog::level::info);
                m_file_logger->set_level(spdlog::level::info);
                break;
            case 3:
                m_console_logger->set_level(spdlog::level::debug);
                m_file_logger->set_level(spdlog::level::debug);
                break;
            case 4:
                m_console_logger->set_level(spdlog::level::err);
                m_file_logger->set_level(spdlog::level::err);
                break;
            case 5:
                m_console_logger->set_level(spdlog::level::critical);
                m_file_logger->set_level(spdlog::level::critical);
                break;
            case 6:
                m_console_logger->set_level(spdlog::level::off);
                m_file_logger->set_level(spdlog::level::off);
                break;
        }

    }
}