#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <NTTEngine/Renderer/Camera.hpp>
#include <NTTEngine/NTTEngine.hpp>


namespace ntt
{
    Camera::Camera(glm::vec3 cameraPos, float fov, 
                    glm::vec3 rotation, glm::vec3 cameraFront, 
                    glm::vec3 cameraUp)
        : fov_(fov), rotation_(rotation), cameraPos_(cameraPos), cameraFront_(cameraFront),
            cameraUp_(cameraUp)
    {

    } 

    Camera::~Camera()
    {

    }

    glm::mat4 Camera::GetViewProjectMatrix()
    {
        auto width = Application::GetApplication()->GetWindow()->GetWidth();
        auto height = Application::GetApplication()->GetWindow()->GetHeight();

        glm::mat4 view = glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
        view = glm::rotate(view, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::rotate(view, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 proj = glm::perspective(glm::radians(fov_), 
                    (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
        return proj * view;
    }
} // namespace ntt
