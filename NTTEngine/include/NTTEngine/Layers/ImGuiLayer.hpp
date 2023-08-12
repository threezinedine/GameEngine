#pragma once
#include <string>
#include <vector>
#include <memory>

#include <imgui.h>
#include <NTTEngine/Layer.hpp>
// #include "ImGuiApplication.hpp"
#include "IImGuiRenderer.hpp"


namespace ntt
{
    class ImGuiLayer: public Layer
    {
        public:
            ImGuiLayer(std::string layerName);
            ~ImGuiLayer() override;

            void OnAttach() override;
            void OnDetach() override;

            void OnUpdate() override;

            void AddApplication(std::shared_ptr<IImGuiRenderer> application, bool visible = true);
        
        protected:
            std::vector<bool*> applicationVisibles_;
            std::vector<std::shared_ptr<IImGuiRenderer>> applications_;
    };    
} // namespace ntt
