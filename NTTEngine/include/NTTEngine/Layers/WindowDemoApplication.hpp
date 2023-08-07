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
            void OnImGuiRender() override;

        private:
            bool showWindow_;
    };
} // namespace ntt
