#include <string>

#include "NTTEngineImGuiLayerSystem/PreInclude.hpp"
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"
#include "NTTEngineImGuiLayerSystem/ImGuiViewportApplication.hpp"

namespace ntt
{
    ImGuiLayer::ImGuiLayer(std::string layerName)
        : Layer(layerName)
    {
        PROFILE_SCOPE();
    }

    ImGuiLayer::~ImGuiLayer()
    {
        PROFILE_SCOPE();

        OnPlatformRelease();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnAttach()
    {
        PROFILE_SCOPE();

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        OnPlatformInitialize();
    }

    void ImGuiLayer::OnDetach()
    {
        PROFILE_SCOPE();
    }

    void ImGuiLayer::OnUpdate(Timestep ts)
    {
        PROFILE_SCOPE();

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

        ImGuiViewportApplication* viewport = ImGuiViewportApplication::GetInstance();

        if (viewport != nullptr)
        {
            viewport->OnImGuiRender(ts);
        }

        ImGui::Render();
        OnPlatformUpdateEnd();
    }

    void ImGuiLayer::AddApplication(std::shared_ptr<IImGuiApplication> application)
    {
        PROFILE_SCOPE();

        applications_.push_back(application);
    }
} // namespace ntt
