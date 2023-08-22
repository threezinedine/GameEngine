#include <string>

#include <imgui.h>
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"

namespace ntt
{
    ImGuiLayer::ImGuiLayer(std::string layerName)
        : Layer(layerName)
    {
        NTT_ENGINE_DEBUG("Start Initializing ImGuiLayer");
        NTT_ENGINE_DEBUG("Finish Initializing ImGuiLayer");
    }

    ImGuiLayer::~ImGuiLayer()
    {
        NTT_ENGINE_DEBUG("Start Delete ImGuiLayer");
        OnPlatformRelease();
        ImGui::DestroyContext();

        NTT_ENGINE_DEBUG("Finish Delete ImGuiLayer");
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        OnPlatformInitialize();
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate(Timestep ts)
    {
        OnPlatformUpdateBegin();
        ImGui::NewFrame();

        bool test = true;
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Views"))
            {
                for (auto appliation: applications_)
                {
                    appliation->MenuItem();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        for (auto application: applications_)
        {
            if (application->IsActive())
            {
                application->OnImGuiRender(ts);
            }
        }

        ImGui::Render();
        OnPlatformUpdateEnd();
    }

    void ImGuiLayer::AddApplication(std::shared_ptr<IImGuiApplication> application)
    {
        applications_.push_back(application);
    }
} // namespace ntt
