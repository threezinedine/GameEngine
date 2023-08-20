#pragma once
#include <string>
#include <spdlog/spdlog.h>


namespace ntt
{
    class Logging
    {
        public:
            Logging();
            virtual ~Logging();

            static void Init();

            void Info(const std::string& message);
            void Debug(const std::string& message);
            void Warn(const std::string& message);
            void Error(const std::string& message);
            void Critical(const std::string& message);

            inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return engineLogger_; }
            inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger() { return applicationLogger_; }

        private:
            static std::shared_ptr<spdlog::logger> engineLogger_;
            static std::shared_ptr<spdlog::logger> applicationLogger_;
    };
} // namespace ntt
