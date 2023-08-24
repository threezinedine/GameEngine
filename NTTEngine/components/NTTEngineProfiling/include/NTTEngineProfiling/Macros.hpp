#pragma once

#ifdef NTT_DEBUG_VERSION
    #define PROFILE_NAME(name) ntt::NTTTimer timer_##__LINE__(name)
    #define PROFILE_SCOPE() PROFILE_NAME(__PRETTY_FUNCTION__)
#else 
    #define PROFILE_NAME(name)
    #define PROFILE_SCOPE()
#endif