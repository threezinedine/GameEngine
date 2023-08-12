#pragma once

#include <string>

#include <NTTEngine/Macros.hpp>
#include <NTTEngine/EventSystem/EventSystem.hpp>

#include "Layers/IImGuiRenderer.hpp"

namespace ntt
{
    class Layer: public IImGuiRenderer
    {
        public:
            Layer(std::string layerName);
            virtual ~Layer();

            virtual void OnAttach();
            virtual void OnDetach();
            virtual void OnUpdate();

            inline const std::string& GetName() const { return layerName_; }
            void OnImGuiRender() override;
            virtual void OnImGuiRenderImpl() {};

            DEFINE_EVENT_INTEFACE_LAYER(WindowClose)
            DEFINE_EVENT_INTEFACE_LAYER(WindowResize)

            DEFINE_EVENT_INTEFACE_LAYER(MouseMove)
            DEFINE_EVENT_INTEFACE_LAYER(MouseClick)
            DEFINE_EVENT_INTEFACE_LAYER(MouseScroll)

            DEFINE_EVENT_INTEFACE_LAYER(KeyPress)
            DEFINE_EVENT_INTEFACE_LAYER(KeyRelease)

        private:
            std::string layerName_;
    }; 
} // namespace ntt
