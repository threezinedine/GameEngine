#include "NTTEngineProfiling/PreInclude.hpp"
#include <iomanip>
#include <iostream>


namespace ntt
{
    NTTTimer::NTTTimer(const char* name, NTTTimerMode timerMode, int afterPoint) 
        : name_(name), mode_(timerMode), afterPoint_(afterPoint)
    {
        start_ = std::chrono::high_resolution_clock::now();
    }

    NTTTimer::~NTTTimer()
    {
        auto end = std::chrono::high_resolution_clock::now();

        NTTInstrument::WriteEvent(
            { 
                name_, 
                std::chrono::time_point_cast<std::chrono::microseconds>(start_).time_since_epoch().count(),
                std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count(),
            }
        );
        // std::cout << "Measure Func " << name_ << ": " 
        //         << std::fixed << std::setprecision(afterPoint_) << GetTime() 
        //         << "(" << GetUnit() << ")" << std::endl;
    }

    uint64_t NTTTimer::GetRawTime()
    {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
    }

    double NTTTimer::GetTime()
    {
        auto duration = GetRawTime();

        switch (mode_)
        {
            case NTTTimer_Sec:
                return duration / 1000000;
            case NTTTimer_MiniSec:
                return duration / 1000;
            default:
                return duration;
        } 
    }

    std::string NTTTimer::GetUnit()
    {
        switch (mode_)
        {
            case NTTTimer_Sec:
                return "s";
            case NTTTimer_MiniSec:
                return "ms";
            default:
                return "us";
        }
    }
} // namespace ntt
