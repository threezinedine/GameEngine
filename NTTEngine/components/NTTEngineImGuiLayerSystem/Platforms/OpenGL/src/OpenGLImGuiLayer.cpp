#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"
#include "NTTEngineLayerSystem/NTTEngineLayerSystem.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"
#include "NTTEngineLog/NTTEngineLog.hpp"


namespace ntt
{
    void ImGuiLayer::OnPlatformInitialize()
    {
        ImGui_ImplGlfw_InitForOpenGL(
            static_cast<GLFWwindow*>(Window::GetInstance()->GetWindow()),
            true
        );
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void ImGuiLayer::OnPlatformUpdateBegin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    void ImGuiLayer::OnPlatformUpdateEnd()
    {
        glViewport(0, 0, Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnPlatformRelease()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
} // namespace ntt
