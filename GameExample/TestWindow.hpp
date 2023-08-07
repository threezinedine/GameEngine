#pragma once
#include <NTTEngine/NTTEngine.hpp>


class TestWindow: public ntt::ImGuiApplication
{
    public:
        TestWindow(std::string windowName)
            : ImGuiApplication(windowName) {}
        void OnImGuiRenderImpl() override 
        {
            static bool testVisible = true;
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Views"))
                {
                    ImGui::MenuItem("Test", NULL, &testVisible);
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            ImGui::Text("Home");
        }
};