#pragma once
#include <string>
#include "ImGuiComponent.hpp"
#include <vector>


namespace ntt
{
    class ImGuiApplication: public IImGuiRenderer
    {
        public:
            ImGuiApplication(std::string windowName);
            virtual ~ImGuiApplication();

            virtual void OnImGuiRender();
            virtual void OnImGuiRenderImpl();

            inline const std::string& GetName() const { return windowName_; }

            void AddComponent(ImGuiComponent* component) { components_.push_back(component); }

        protected:
            std::vector<ImGuiComponent*> components_;

        private:
            std::string windowName_;
    }; 
} // namespace ntt
