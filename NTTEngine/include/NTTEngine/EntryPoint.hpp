#pragma once

#include "Application.hpp"
#include "NTTEngine/NTTEngine.hpp"

using namespace ntt;


#ifndef NTT_ENGINE_BUILD
Application* CreateApplication();

int main(int argc, char** argv)
{
    ntt::NTTInstrument::StartSession("./initialize-session.json");
    Logging::Init();

    auto application = CreateApplication();

    application->OnSetup();
    ntt::NTTInstrument::EndSession();

    ntt::NTTInstrument::StartSession("./running-session.json");
    application->OnRun();
    ntt::NTTInstrument::EndSession();

    ntt::NTTInstrument::StartSession("./release-session.json");
    delete application;

    ntt::Window::Release();
    ntt::NTTInstrument::EndSession();
    return 0;
}
#endif