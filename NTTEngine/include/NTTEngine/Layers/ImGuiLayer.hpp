#pragma once
#include <string>

#include <imgui.h>
#include <NTTEngine/Layer.hpp>


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
            virtual void OnImGuiRender();
        
        protected:
    };    
} // namespace ntt
