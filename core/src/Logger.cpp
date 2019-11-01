#include "Logger.h"

namespace yage {

    std::shared_ptr<spdlog::logger> Logger::mConsoleLogger = nullptr;
    std::shared_ptr<spdlog::logger> Logger::mFileLogger = nullptr;

    void Logger::Init() {
        mConsoleLogger = spdlog::stdout_color_mt("YAGE Console Logger");
        mConsoleLogger->flush_on(spdlog::level::err);

        try {
            mFileLogger = spdlog::basic_logger_mt(std::string("YAGE File LOGGER"), "LOG.txt");
            className:
            mFileLogger->flush_on(spdlog::level::err);
        }
        catch (const spdlog::spdlog_ex &ex) {
            mFileLogger->warn("Failed to init file logger");
        }
        mFileLogger->info("", "");
       SetLogLevel(YAGE_LOG_LEVEL_DEBUG);
    }

    void Logger::SetLogLevel(int level) {
        switch (level) {
            case 1:
                mConsoleLogger->set_level(spdlog::level::trace);
                mFileLogger->set_level(spdlog::level::trace);
                break;
            case 2:
                mConsoleLogger->set_level(spdlog::level::info);
                mFileLogger->set_level(spdlog::level::info);
                break;
            case 3:
                mConsoleLogger->set_level(spdlog::level::debug);
                mFileLogger->set_level(spdlog::level::debug);
                break;
            case 4:
                mConsoleLogger->set_level(spdlog::level::err);
                mFileLogger->set_level(spdlog::level::err);
                break;
            case 5:
                mConsoleLogger->set_level(spdlog::level::critical);
                mFileLogger->set_level(spdlog::level::critical);
                break;
            case 6:
                mConsoleLogger->set_level(spdlog::level::off);
                mFileLogger->set_level(spdlog::level::off);
                break;
        }

    }
}