#pragma once
#include <string>
#include <vector>
#include <memory>

#include <imgui.h>
#include "IImGuiApplication.hpp"
#include "NTTEngineCore/NTTEngineCore.hpp"


namespace ntt
{
    class ImGuiLayer: public Layer
    {
        public:
            ImGuiLayer(std::string layerName);
            ~ImGuiLayer() override;

            void OnAttach() override;
            void OnDetach() override;

            void OnUpdate(Timestep ts) override;

            void AddApplication(std::shared_ptr<IImGuiApplication> application);
        
        protected:
            std::vector<std::shared_ptr<IImGuiApplication>> applications_;
    };    
} // namespace ntt
