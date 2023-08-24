#include "NTTEngineImGuiLayerSystem/PreInclude.hpp"
#include "NTTEngineImGuiLayerSystem/WindowDemoApplication.hpp"



namespace ntt
{
    WindowDemoApplication::~WindowDemoApplication()
    {

    }

    void WindowDemoApplication::OnImGuiRender(Timestep ts)
    {
        PROFILE_SCOPE();

        ImGui::ShowDemoWindow(&showWindow_);
    }
} // namespace ntt

