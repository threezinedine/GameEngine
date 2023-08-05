#pragma once
#include <string>

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
    };    
} // namespace ntt
