#include <string>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <NTTEngine/Core.hpp>
#include <NTTEngine/Layer.hpp>
#include <NTTEngine/Layers/ImGuiLayer.hpp>
#include <NTTEngine/Application.hpp>


namespace ntt
{
    ImGuiLayer::ImGuiLayer(std::string layerName)
        : Layer(layerName) 
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(
            static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetWindow()),
            true
        );
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = true;
        if (show_demo_window)
        {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGui::Render();
        IWindow* win = Application::GetApplication()->GetWindow();
        glViewport(0, 0, win->GetWidth(), win->GetHeight());

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(static_cast<GLFWwindow*>(win->GetWindow()));
    }
} // namespace ntt
