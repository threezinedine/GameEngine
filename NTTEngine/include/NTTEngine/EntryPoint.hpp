#pragma once

#include "Core.hpp"
#include "Logging.hpp"
#include "Application.hpp"

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
    application->Setup();
    NTT_ENGINE_INFO("Setup the game successfully");

    NTT_ENGINE_INFO("Start the game");
    application->Run();
    NTT_ENGINE_INFO("Stop the game");

    delete application;
    return 0;
}
#endif