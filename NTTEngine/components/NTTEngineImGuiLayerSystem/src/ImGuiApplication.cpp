#include <string>

#include "NTTEngineImGuiLayerSystem/PreInclude.hpp"
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"


namespace ntt
{
    ImGuiApplication::ImGuiApplication(std::string windowName)
        : windowName_(windowName)
    {
        PROFILE_SCOPE();

        storage_ = std::make_shared<ntt::Storage>(
            std::make_shared<ntt::RealFileSystem>("./" + GetName() + "-application.json")
        );

        isActive_ = std::make_unique<ntt::ThreadValue<bool>>(true, storage_, "isActive");
    }    

    ImGuiApplication::~ImGuiApplication()
    {
        PROFILE_SCOPE();

        isActive_->Save();
        storage_->Save();
    }

    void ImGuiApplication::OnImGuiRender(Timestep ts)
    {
        PROFILE_SCOPE();

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

    void ImGuiApplication::MenuItem()
    {
        ImGui::MenuItem(GetName().c_str(), nullptr, isActive_->GetPointer(), true);    
    }
} // namespace ntt
