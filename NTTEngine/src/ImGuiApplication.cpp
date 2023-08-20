#include <string>
#include <imgui.h>

#include <NTTEngine/Core.hpp>
#include "NTTEngineLog/NTTEngineLog.hpp"
#include <NTTEngine/Layers/Layers.hpp>


namespace ntt
{
    ImGuiApplication::ImGuiApplication(std::string windowName)
        : windowName_(windowName)
    {

    }    

    ImGuiApplication::~ImGuiApplication()
    {
        NTT_ENGINE_DEBUG("Delete Imgui application");
    }

    void ImGuiApplication::OnImGuiRender(Timestep ts)
    {
        ImGui::Begin(windowName_.c_str());
        OnImGuiRenderImpl(ts);
        for (auto component: components_)
        {
            component->OnImGuiRender(ts);
        }
        ImGui::End();
    }

    void ImGuiApplication::OnImGuiRenderImpl(Timestep ts)
    {

    }
} // namespace ntt
