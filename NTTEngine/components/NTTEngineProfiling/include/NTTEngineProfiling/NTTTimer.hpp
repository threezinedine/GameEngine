#pragma once
#include "PreInclude.hpp"
#include <string>


namespace ntt
{
    enum NTTTimerMode
    {
        NTTTimer_MiniSec,
        NTTTimer_Sec,
        NTTTimer_MicroSec,
    };

    class NTTTimer
    {
        public:
            NTTTimer(const char* name, 
                    NTTTimerMode timerMode = NTTTimer_MiniSec, int afterPoint = 3);
            ~NTTTimer();

        private:
            std::chrono::high_resolution_clock::time_point start_;
            const char* name_;
            NTTTimerMode mode_;
            int afterPoint_;

            uint64_t GetRawTime();
            double GetTime();
            std::string GetUnit();
    };
} // namespace ntt
