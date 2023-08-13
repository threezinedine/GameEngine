#pragma once
#include <glm/glm.hpp>
#include "NTTEngine/Utils/Utils.hpp"


namespace ntt
{
    class Camera 
    {
        public:
            Camera(NTTVec3 cameraPos, float fov,
                    NTTVec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
                    NTTVec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f), 
                    NTTVec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));
            ~Camera();

            glm::mat4 GetViewProjectMatrix();

            inline float* GetFovPointer() { return &fov_; }

            inline NTTVec3& GetCameraPos() { return cameraPos_; }
            inline NTTVec3& GetCameraFront() { return cameraFront_; }
            inline NTTVec3& GetCameraUp() { return cameraUp_; }
            inline NTTVec3& GetRotation() { return rotation_; }

        private:
            float fov_;
            NTTVec3 rotation_;
            NTTVec3 cameraPos_;
            NTTVec3 cameraFront_;
            NTTVec3 cameraUp_;
    }; 
} // namespace ntt
