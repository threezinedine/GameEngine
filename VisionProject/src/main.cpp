#include <iostream>
#include <NTTEngine/EntryPoint.hpp>
#include <VisionApplication.hpp>
#include <NTTEngine/NTTEngine.hpp>


ntt::Application* CreateApplication()
{
    return new VisionApplication();
}