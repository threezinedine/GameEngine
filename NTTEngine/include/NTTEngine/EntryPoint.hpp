#pragma once

#include "Application.hpp"


#ifndef NTT_ENGINE_BUILD
ntt::Application* CreateApplication();

int main(int argc, char** argv)
{
    auto application = CreateApplication();
    application->Run();
    delete application;
    return 0;
}

#else

#endif