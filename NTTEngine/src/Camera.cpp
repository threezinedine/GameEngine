#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <NTTEngine/Renderer/Camera.hpp>
#include <NTTEngine/NTTEngine.hpp>


namespace ntt
{
    Camera::Camera(NTTVec3 cameraPos, float fov, 
                    NTTVec3 rotation, NTTVec3 cameraFront, 
                    NTTVec3 cameraUp)
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
        auto rotation = rotation_.GetGlmVec3();

        glm::mat4 view = glm::lookAt(cameraPos_.GetGlmVec3(), 
                                cameraPos_.GetGlmVec3() + cameraFront_.GetGlmVec3(), 
                                cameraUp_.GetGlmVec3());

        view = glm::rotate(view, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::rotate(view, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 proj = glm::perspective(glm::radians(fov_), 
                    (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
        return proj * view;
    }
} // namespace ntt
