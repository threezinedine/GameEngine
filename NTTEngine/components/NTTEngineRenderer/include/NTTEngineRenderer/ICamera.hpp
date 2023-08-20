#pragma once
#include <glm/glm.hpp>

#include "NTTEngineCore/NTTEngineCore.hpp"
#include "NTTEngineEventSystem/NTTEngineEventSystem.hpp"


namespace ntt
{
    class ICamera
    {
        public:
            virtual glm::mat4 GetViewProjectMatrix() = 0;

            virtual void OnUpdate(Timestep ts) = 0;
            virtual void OnImGuiRender(Timestep ts) = 0;

            virtual void OnMouseScroll(MouseScrollEvent& event) = 0;
            virtual void OnWindowResize(WindowResizeEvent& event) = 0;
    }; 
} // namespace ntt
