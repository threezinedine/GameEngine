#include "NTTEngineImGuiLayerSystem/PreInclude.hpp"
#include "NTTEngineImGuiLayerSystem/ImGuiViewportApplication.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"
#include "NTTEngineCore/NTTEngineCore.hpp"


namespace ntt
{
    ImGuiViewportApplication* ImGuiViewportApplication::instance_ = nullptr;

    ImGuiViewportApplication::ImGuiViewportApplication()
        : ImGuiApplication("Viewport")
    {
        frameBuffer_ = std::make_shared<FrameBuffer>
        (
            Window::GetInstance()->GetWidth(),
            Window::GetInstance()->GetHeight()
        );
    }

    ImGuiViewportApplication::~ImGuiViewportApplication()
    {

    }

    void ImGuiViewportApplication::OnImGuiRender(Timestep ts)
    {
        ImGui::Begin("Viewport");
        if (frameBuffer_ != nullptr)
        {
            ImTextureID frameId = (ImTextureID)frameBuffer_->GetColorTextureId();
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImGui::Image(frameId, { windowSize.x * 0.95, windowSize.y * 0.95 });
        }
        ImGui::End();
    }
} // namespace ntt
