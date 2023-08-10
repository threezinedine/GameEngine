#include <iostream>
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <NTTEngine/Core.hpp>

void ClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool PrintOutError(const std::string& file, int line)
{
    if(GLenum errorCode = glGetError())
    {
        std::cout << "Error (0x" << std::hex << errorCode << ") at: " 
                    << file << ":" << std::dec << line << std::endl;
        return false;
    }
    else 
    {
        return true;
    }
}