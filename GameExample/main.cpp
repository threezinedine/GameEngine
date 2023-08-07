#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <glm/vec3.hpp>

#include <NTTEngine/NTTEngine.hpp>
#include "GameExampleApplication.hpp"
#include <NTTEngine/EntryPoint.hpp>



ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}