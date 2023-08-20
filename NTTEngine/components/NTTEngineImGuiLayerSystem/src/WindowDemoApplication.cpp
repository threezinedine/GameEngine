#include <imgui.h>
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"

#include "NTTEngineLog/NTTEngineLog.hpp"


namespace ntt
{
    WindowDemoApplication::~WindowDemoApplication()
    {
        NTT_ENGINE_DEBUG("Delete Window Demo Application");
    }

    void WindowDemoApplication::OnImGuiRender(Timestep ts)
    {
        ImGui::ShowDemoWindow(&showWindow_);
    }
} // namespace ntt

