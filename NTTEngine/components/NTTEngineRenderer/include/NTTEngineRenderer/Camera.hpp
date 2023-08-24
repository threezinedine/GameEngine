#pragma once
#include <memory>
#include <glm/glm.hpp>


namespace ntt
{
    class Timestep;
    class MouseScrollEvent;
    class WindowResizeEvent;
    class Storage;
    class NTTVec3;

    class Camera
    {
        public:
            Camera();
            ~Camera();

            glm::mat4 GetViewProjectMatrix();

            inline std::shared_ptr<NTTVec3>& GetCameraPos() { return cameraPos_; }
            inline std::shared_ptr<NTTVec3>& GetCameraFront() { return cameraFront_; }
            inline std::shared_ptr<NTTVec3>& GetCameraUp() { return cameraUp_; }
            inline std::shared_ptr<NTTVec3>& GetRotation() { return rotation_; }

            void OnUpdate(Timestep ts);
            void OnImGuiRender(Timestep ts);
            void OnMouseScroll(MouseScrollEvent& event);
            void OnWindowResize(WindowResizeEvent& event);

        private:
            std::shared_ptr<Storage> storage_;

            std::shared_ptr<NTTVec3> rotation_;
            std::shared_ptr<NTTVec3> cameraPos_;
            std::shared_ptr<NTTVec3> cameraFront_;
            std::shared_ptr<NTTVec3> cameraUp_;

            float* fov_;
            float* moveSpeed_;
            float* rotateSpeed_;
            float* zoomLevel_;
    }; 
} // namespace ntt
