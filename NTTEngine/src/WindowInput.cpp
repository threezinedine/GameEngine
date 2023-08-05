#include <utility>
#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <NTTEngine/Application.hpp>
#include <NTTEngine/Platforms/Platforms.hpp>


namespace ntt
{
    GLFWwindow* WindowInput::GetWindow()
    {
        return static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetWindow()); 
    }

    std::pair<int, int> WindowInput::GetMousePositionImpl()
    {
        double mouseX, mouseY;
        glfwGetCursorPos(GetWindow(), &mouseX, &mouseY);
        return std::make_pair((int)mouseX, (int)mouseY);
    }

    bool WindowInput::IsButtonLeftClickedImpl()
    {
        return glfwGetMouseButton(GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }

    bool WindowInput::IsKeyPressedImpl(int key)
    {
        return glfwGetKey(GetWindow(), key) == GLFW_PRESS;
    }
} // namespace ntt
