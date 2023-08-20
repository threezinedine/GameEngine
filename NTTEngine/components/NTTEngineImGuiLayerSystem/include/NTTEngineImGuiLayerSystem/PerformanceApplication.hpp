#pragma once

#include "ImGuiApplication.hpp"


namespace ntt
{
    class PerformanceApplication: public ImGuiApplication
    {
        public:
            PerformanceApplication(int location = 0, bool open = true);
            ~PerformanceApplication();

            void OnImGuiRender(Timestep ts);

        private:
            int location_;
            bool open_;
    };
} // namespace ntt
