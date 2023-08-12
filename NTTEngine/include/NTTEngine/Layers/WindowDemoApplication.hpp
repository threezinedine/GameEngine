#pragma once
#include <string>

#include "ImGuiApplication.hpp"


namespace ntt
{
    class WindowDemoApplication: public ImGuiApplication
    {
        public:
            WindowDemoApplication(): 
                    ImGuiApplication("Demo window"), showWindow_(true) {}

            ~WindowDemoApplication();
            void OnImGuiRender(Timestep ts) override;

        private:
            bool showWindow_;
    };
} // namespace ntt
