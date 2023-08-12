#pragma once
#include <glm/glm.hpp>


namespace ntt
{
    class Camera 
    {
        public:
            Camera(glm::vec3 cameraPos, float fov,
                    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f), 
                    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));
            ~Camera();

            glm::mat4 GetViewProjectMatrix();

            inline float* GetCameraPosPointer() { return &cameraPos_.x; }
            inline float* GetCameraFrontPointer() { return &cameraFront_.x; }
            inline float* GetCameraUpPointer() { return &cameraUp_.x; }
            inline float* GetFovPointer() { return &fov_; }
            inline float* GetRotationPointer() { return &rotation_.x; }

        private:
            float fov_;
            glm::vec3 rotation_;
            glm::vec3 cameraPos_;
            glm::vec3 cameraFront_;
            glm::vec3 cameraUp_;
    }; 
} // namespace ntt
