#pragma once

#include "ImGuiApplication.hpp"


namespace ntt
{
    class PerformanceApplication: public ImGuiApplication
    {
        public:
            PerformanceApplication();
            ~PerformanceApplication();

            void OnImGuiRender(Timestep ts);

        private:

    };
} // namespace ntt
