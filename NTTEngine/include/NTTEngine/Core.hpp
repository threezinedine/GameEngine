#pragma once


#define NTT_ENGINE_INFO(...)        ntt::Logging::GetEngineLogger()->info(__VA_ARGS__)
#define NTT_ENGINE_DEBUG(...)       ntt::Logging::GetEngineLogger()->debug(__VA_ARGS__)
#define NTT_ENGINE_WARN(...)        ntt::Logging::GetEngineLogger()->warn(__VA_ARGS__)
#define NTT_ENGINE_ERROR(...)       ntt::Logging::GetEngineLogger()->error(__VA_ARGS__)
#define NTT_ENGINE_CRITICAL(...)    ntt::Logging::GetEngineLogger()->critical(__VA_ARGS__)

#define NTT_APPLICATION_INFO(...)        ntt::Logging::GetApplicationLogger()->info(__VA_ARGS__)
#define NTT_APPLICATION_DEBUG(...)       ntt::Logging::GetApplicationLogger()->debug(__VA_ARGS__)
#define NTT_APPLICATION_WARN(...)        ntt::Logging::GetApplicationLogger()->warn(__VA_ARGS__)
#define NTT_APPLICATION_ERROR(...)       ntt::Logging::GetApplicationLogger()->error(__VA_ARGS__)
#define NTT_APPLICATION_CRITICAL(...)    ntt::Logging::GetApplicationLogger()->critical(__VA_ARGS__)