#pragma once
#include <string>
#include <vector>
#include <memory>
#include "ImGuiComponent.hpp"


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

            void AddComponent(std::shared_ptr<IImGuiRenderer> component) { components_.push_back(component); }

        protected:
            std::vector<std::shared_ptr<IImGuiRenderer>> components_;

        private:
            std::string windowName_;
    }; 
} // namespace ntt
