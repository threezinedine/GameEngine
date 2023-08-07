#pragma once
#include <NTTEngine/NTTEngine.hpp>


class TestWindow: public ntt::ImGuiApplication
{
    public:
        TestWindow(std::string windowName)
            : ImGuiApplication(windowName) {}
        void OnImGuiRenderImpl() override 
        {
            ImGui::Text("Home");
        }
};