#include <NTTEngine/Layers/WindowDemoApplication.hpp>
#include <imgui.h>


namespace ntt
{
    void WindowDemoApplication::OnImGuiRender()
    {
        ImGui::ShowDemoWindow(&showWindow_);
    }
} // namespace ntt

