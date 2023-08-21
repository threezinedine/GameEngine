#include "UartApplication.hpp"
#include "NTTEngine/EntryPoint.hpp"


ntt::Application* CreateApplication()
{
    return new UartApplication();
}