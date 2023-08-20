#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IImGuiApplication.hpp"
#include "ImGuiComponent.hpp"
#include "NTTEngineCore/NTTEngineCore.hpp"
#include "NTTEngineThreadSystem/NTTEngineThreadSystem.hpp"


namespace ntt
{
    class ImGuiApplication: public IImGuiApplication
    {
        public:
            ImGuiApplication(std::string windowName);
            virtual ~ImGuiApplication();

            virtual void OnImGuiRender(Timestep ts);
            virtual void OnImGuiRenderImpl(Timestep ts);

            inline const std::string& GetName() const { return windowName_; }

            void AddComponent(std::shared_ptr<IImGuiRenderer> component) { components_.push_back(component); }
            
            virtual bool IsActive() override { return isActive_->GetValue(); }
            virtual void MenuItem() override;

        protected:
            std::vector<std::shared_ptr<IImGuiRenderer>> components_;
            std::shared_ptr<ntt::Storage> storage_;

        private:
            std::string windowName_;
            std::unique_ptr<ntt::ThreadValue<bool>> isActive_;
    }; 
} // namespace ntt
