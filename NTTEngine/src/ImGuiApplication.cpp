#include <string>
#include <imgui.h>

#include <NTTEngine/Layers/Layers.hpp>


namespace ntt
{
    ImGuiApplication::ImGuiApplication(std::string windowName)
        : windowName_(windowName)
    {

    }    

    ImGuiApplication::~ImGuiApplication()
    {

    }

    void ImGuiApplication::OnImGuiRender()
    {
        ImGui::Begin(windowName_.c_str());
        OnImGuiRenderImpl();
        ImGui::End();
    }

    void ImGuiApplication::OnImGuiRenderImpl()
    {

    }
} // namespace ntt
