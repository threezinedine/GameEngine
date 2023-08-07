#pragma once
#include <string>


namespace ntt
{
    class ImGuiApplication
    {
        public:
            ImGuiApplication(std::string windowName);
            ~ImGuiApplication();

            virtual void OnImGuiRender();
            virtual void OnImGuiRenderImpl();

            inline std::string GetName() const { return windowName_; }
        private:
            std::string windowName_;
    }; 
} // namespace ntt
