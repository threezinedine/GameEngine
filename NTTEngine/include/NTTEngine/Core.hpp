#pragma once
#include "Logging.hpp"


#define NTT_ENGINE_INFO(...)            Logging::GetEngineLogger()->info(__VA_ARGS__)
#define NTT_ENGINE_DEBUG(...)           Logging::GetEngineLogger()->debug(__VA_ARGS__)
#define NTT_ENGINE_WARN(...)            Logging::GetEngineLogger()->warn(__VA_ARGS__)
#define NTT_ENGINE_ERROR(...)           Logging::GetEngineLogger()->error(__VA_ARGS__)
#define NTT_ENGINE_CRITICAL(...)        Logging::GetEngineLogger()->critical(__VA_ARGS__)

#define NTT_APPLICATION_INFO(...)       ntt::Logging::GetApplicationLogger()->info(__VA_ARGS__)
#define NTT_APPLICATION_DEBUG(...)      ntt::Logging::GetApplicationLogger()->debug(__VA_ARGS__)
#define NTT_APPLICATION_WARN(...)       ntt::Logging::GetApplicationLogger()->warn(__VA_ARGS__)
#define NTT_APPLICATION_ERROR(...)      ntt::Logging::GetApplicationLogger()->error(__VA_ARGS__)
#define NTT_APPLICATION_CRITICAL(...)   ntt::Logging::GetApplicationLogger()->critical(__VA_ARGS__)

#define GL_CALL(x) ClearError(); \
    x; \
    PrintOutError(__FILE__, __LINE__);

void ClearError();
bool PrintOutError(const std::string& file, int line);