#pragma once

#include <string>

#include <NTTEngine/Macros.hpp>
#include <NTTEngine/EventSystem/EventSystem.hpp>


namespace ntt
{
    class Layer
    {
        public:
            Layer(std::string layerName);
            ~Layer();

            virtual void OnAttach();
            virtual void OnDetach();
            virtual void OnUpdate();

            inline std::string GetLayerName() const { return layerName_; }

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
