#include <chrono>
#include "NTTEngineUtils/NTTEngineUtils.hpp"


namespace ntt
{
    TimePlan::TimePlan(int miliSeconds)
        : miliSeconds_(miliSeconds)
    {
        startTime_ = std::chrono::high_resolution_clock::now();
    }

    TimePlan::~TimePlan()
    {

    }

    bool TimePlan::IsTriggered()
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count();

        if (elapsedTime > miliSeconds_)
        {
            startTime_ = endTime;
            return true;
        }
        else 
        {
            return false;
        }
    }
} // namespace ntt
