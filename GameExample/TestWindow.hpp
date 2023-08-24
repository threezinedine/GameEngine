#pragma once
#include <NTTEngine/NTTEngine.hpp>


class TestWindow: public ntt::ImGuiApplication
{
    public:
        TestWindow(std::string windowName)
            : ImGuiApplication(windowName) 
        {
            PROFILE_SCOPE();
        }

        ~TestWindow()
        {
            PROFILE_SCOPE();
        }

        void OnImGuiRenderImpl(ntt::Timestep ts) override 
        {
            PROFILE_SCOPE();

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