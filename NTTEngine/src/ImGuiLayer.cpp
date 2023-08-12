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
        NTT_ENGINE_DEBUG("Delete ImGuiLayer");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        for (auto visible: applicationVisibles_)
        {
            if (visible != nullptr)
            {
                delete visible;
            }
        }
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        bool test = true;
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Views"))
            {
                for (int i=0; i<applications_.size(); i++)
                {
                    ImGui::MenuItem(applications_[i]->GetName().c_str(), NULL, applicationVisibles_[i]);
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        for (int i=0; i<applications_.size(); i++)
        {
            if (*applicationVisibles_[i])
            {
                applications_[i]->OnImGuiRender();
            }
        }

        ImGui::Render();
        IWindow* win = Application::GetApplication()->GetWindow();
        glViewport(0, 0, win->GetWidth(), win->GetHeight());

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::AddApplication(std::shared_ptr<IImGuiRenderer> application, bool visible)
    {
        applicationVisibles_.push_back(new bool(visible));
        applications_.push_back(application);
    }
} // namespace ntt
