#include <string>
#include <imgui.h>

#include <NTTEngine/Core.hpp>
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
        for (auto component: components_)
        {
            if (component != nullptr)
            {
                delete component;
            }
        }
    }

    void ImGuiApplication::OnImGuiRender()
    {
        ImGui::Begin(windowName_.c_str());
        OnImGuiRenderImpl();
        for (auto component: components_)
        {
            component->OnImGuiRender();
        }
        ImGui::End();
    }

    void ImGuiApplication::OnImGuiRenderImpl()
    {

    }
} // namespace ntt
