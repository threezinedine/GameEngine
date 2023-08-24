#include <algorithm>
#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

#include "NTTEngineRenderer/PreInclude.hpp"
#include "Storage.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"
#include "NTTEngineUtils/NTTEngineUtils.hpp"
#include "NTTEngineRenderer/Camera.hpp"


namespace ntt
{
    Camera::Camera()
    {
        PROFILE_SCOPE();

        std::shared_ptr<ntt::IFileSystem> file 
                = std::make_shared<ntt::RealFileSystem>("./default-camera.json");

        storage_ = std::make_shared<ntt::Storage>(file);

        auto camPos = storage_->GetValue<std::vector<float>>("camPos", std::vector<float> {0, 0, 45});
        auto rotation = storage_->GetValue<std::vector<float>>("rotation", std::vector<float> {0, 0, 0});
        auto camFront = storage_->GetValue<std::vector<float>>("camFront", std::vector<float> {0, 0, -1});
        auto camUp = storage_->GetValue<std::vector<float>>("camUp", std::vector<float> {0, 1, 0});

        cameraPos_ = std::make_shared<NTTVec3>(std::vector<float>{0, 0, 45}, storage_, "camPos");
        rotation_ = std::make_shared<NTTVec3>(std::vector<float>{0, 0, 0}, storage_, "rotation");
        cameraFront_ = std::make_shared<NTTVec3>(std::vector<float>{0, 0, -1}, storage_, "camFront");
        cameraUp_ = std::make_shared<NTTVec3>(std::vector<float>{0, 1, 0}, storage_, "camUp");

        fov_ = new float(storage_->GetValue<float>("fov", 1.57));
        moveSpeed_ = new float(storage_->GetValue<float>("moveSpeed", 1));
        rotateSpeed_ = new float(storage_->GetValue<float>("rotateSpeed", 1));
        zoomLevel_ = new float(storage_->GetValue<float>("zoomLevel", 1));
    } 

    Camera::~Camera()
    {
        PROFILE_SCOPE();

        cameraPos_->Save();
        cameraFront_->Save();
        cameraUp_->Save();
        rotation_->Save();

        storage_->SetValue<float>("fov", *fov_);
        storage_->SetValue<float>("moveSpeed", *moveSpeed_);
        storage_->SetValue<float>("rotateSpeed", *rotateSpeed_);
        storage_->SetValue<float>("zoomLevel", *zoomLevel_);

        storage_->Save();

        delete fov_;
        delete moveSpeed_;
        delete rotateSpeed_;
        delete zoomLevel_;
    }

    glm::mat4 Camera::GetViewProjectMatrix()
    {
        auto width = Window::GetInstance()->GetWidth();
        auto height = Window::GetInstance()->GetHeight();
        auto rotation = rotation_->GetGlmVec3();
        auto camPosVec = cameraPos_->GetGlmVec3();

        glm::mat4 view = glm::lookAt(camPosVec * *zoomLevel_, 
                                camPosVec * *zoomLevel_ + cameraFront_->GetGlmVec3(), 
                                cameraUp_->GetGlmVec3());

        view = glm::rotate(view, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::rotate(view, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 proj = glm::perspective(glm::radians(*fov_), 
                    (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
        return proj * view;
    }


    void Camera::OnUpdate(Timestep ts)
    {
        PROFILE_SCOPE();

        if (Window::IsKeyPressed(NTT_KEY_A))
        {
            cameraPos_->GetGlmVec3().x += *moveSpeed_ * (float)ts * *zoomLevel_;
        }
        if (Window::IsKeyPressed(NTT_KEY_D))
        {
            cameraPos_->GetGlmVec3().x -= *moveSpeed_ * (float)ts * *zoomLevel_;
        }
        if (Window::IsKeyPressed(NTT_KEY_W))
        {
            cameraPos_->GetGlmVec3().y -= *moveSpeed_ * (float)ts * *zoomLevel_;
        }
        if (Window::IsKeyPressed(NTT_KEY_S))
        {
            cameraPos_->GetGlmVec3().y += *moveSpeed_ * (float)ts * *zoomLevel_;
        }
        if (Window::IsKeyPressed(NTT_KEY_R))
        {
            rotation_->GetGlmVec3().z += *rotateSpeed_ * (float)ts;
        }
        if (Window::IsKeyPressed(NTT_KEY_Q))
        {
            rotation_->GetGlmVec3().z -= *rotateSpeed_ * (float)ts;
        }
    }

    void Camera::OnImGuiRender(Timestep ts)
    {
        PROFILE_SCOPE();

        ImGui::InputFloat3("Camera Position", cameraPos_->GetFirstPointer());

        ImGui::SliderFloat3("Camera Rotation", rotation_->GetFirstPointer(), -180, 180);

        ImGui::SliderFloat("Camera Fov", fov_, 0, 3.14);
        ImGui::SliderFloat("Rotation Speed", rotateSpeed_, 0, 180);
        ImGui::SliderFloat("Move Speed", moveSpeed_, 0, 5);
    }

    void Camera::OnMouseScroll(MouseScrollEvent& event)
    {
        *zoomLevel_ += (float)event.GetYOffset() * 0.1;
        *zoomLevel_ = std::min(*zoomLevel_, 1.0f);
    }

    void Camera::OnWindowResize(WindowResizeEvent& event)
    {

    }

} // namespace ntt
