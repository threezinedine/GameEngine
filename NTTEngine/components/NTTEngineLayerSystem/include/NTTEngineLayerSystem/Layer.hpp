#pragma once

#include <string>

#include "./Macros.hpp"
#include "NTTEngineEventSystem/NTTEngineEventSystem.hpp"

#include "IImGuiRenderer.hpp"

namespace ntt
{
    class Layer: public IImGuiRenderer
    {
        public:
            Layer(std::string layerName);
            virtual ~Layer();

            virtual void OnAttach();
            virtual void OnDetach();
            virtual void OnUpdate(Timestep ts);

            inline const std::string& GetName() const { return layerName_; }
            void OnImGuiRender(Timestep ts) override;
            virtual void OnImGuiRenderImpl(Timestep ts) {};

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
