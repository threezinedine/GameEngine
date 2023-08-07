#pragma once
#include <string>
#include <vector>

#include <imgui.h>
#include <NTTEngine/Layer.hpp>
#include "ImGuiApplication.hpp"


namespace ntt
{
    class ImGuiLayer: public Layer
    {
        public:
            ImGuiLayer(std::string layerName);
            ~ImGuiLayer();

            void OnAttach() override;
            void OnDetach() override;

            void OnUpdate() override;

            void AddApplication(ImGuiApplication* application);
        
        protected:
            std::vector<ImGuiApplication*> applications_;
    };    
} // namespace ntt
