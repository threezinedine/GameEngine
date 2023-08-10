#pragma once
#include <chrono>


namespace ntt
{
    class TimePlan
    {
        public:
            TimePlan(int miliSeconds = 0);
            ~TimePlan();

            bool IsTriggered();

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
            int miliSeconds_;
    }; 
} // namespace ntt
