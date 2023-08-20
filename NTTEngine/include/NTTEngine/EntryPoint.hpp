#pragma once

#include "Application.hpp"
#include "NTTEngineLog/NTTEngineLog.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"

using namespace ntt;


#ifndef NTT_ENGINE_BUILD
Application* CreateApplication();

int main(int argc, char** argv)
{
    Logging::Init();

    NTT_ENGINE_INFO("Initialize the game");
    auto application = CreateApplication();
    NTT_ENGINE_INFO("Intialze the game successfully");

    NTT_ENGINE_INFO("Setup the game");
    application->OnSetup();
    NTT_ENGINE_INFO("Setup the game successfully");

    NTT_ENGINE_INFO("Start the game");
    application->OnRun();
    NTT_ENGINE_INFO("Stop the game");

    delete application;

    NTT_ENGINE_DEBUG("Start Release Window");
    Window::Release();
    NTT_ENGINE_DEBUG("Finish Release Window");
    return 0;
}
#endif