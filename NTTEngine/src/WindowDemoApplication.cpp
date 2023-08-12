#include <imgui.h>
#include <NTTEngine/Core.hpp>
#include <NTTEngine/Layers/WindowDemoApplication.hpp>


namespace ntt
{
    WindowDemoApplication::~WindowDemoApplication()
    {
        NTT_ENGINE_DEBUG("Delete Window Application");
    }

    void WindowDemoApplication::OnImGuiRender(Timestep ts)
    {
        ImGui::ShowDemoWindow(&showWindow_);
    }
} // namespace ntt

