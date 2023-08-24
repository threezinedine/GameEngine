#include <iostream>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "NTTEngineLog/Logging.hpp"


namespace ntt
{
    std::shared_ptr<spdlog::logger> Logging::engineLogger_;
    std::shared_ptr<spdlog::logger> Logging::applicationLogger_;

    void Logging::Init()
    {
        spdlog::set_pattern("[%l] [%c] [%n] %v");
        engineLogger_ = spdlog::stdout_color_mt("Engine");   
    #ifdef NTT_DEBUG_VERSION
        engineLogger_->set_level(spdlog::level::debug);
    #else
        engineLogger_->set_level(spdlog::level::info);
    #endif
        applicationLogger_ = spdlog::stdout_color_mt("Application");
        applicationLogger_->set_level(spdlog::level::trace);
    }

    void Logging::Info(const std::string& message)
    {
        spdlog::info(message);
    }

    void Logging::Debug(const std::string& message)
    {
        spdlog::debug(message);
    }

    void Logging::Warn(const std::string& message)
    {
        spdlog::warn(message);
    }

    void Logging::Error(const std::string& message)
    {
        spdlog::error(message);
    }

    void Logging::Critical(const std::string& message)
    {
        spdlog::critical(message);
    }
} // namespace ntt
