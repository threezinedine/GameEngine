#pragma once

#include "Logging.hpp"
#include "Application.hpp"


#ifndef NTT_ENGINE_BUILD
ntt::Application* CreateApplication();

int main(int argc, char** argv)
{
    ntt::Logging::Init();
    NTT_ENGINE_INFO("Start the game");

    auto application = CreateApplication();
    application->Run();

    NTT_ENGINE_INFO("Stop the game");
    delete application;
    return 0;
}

#else

#endif