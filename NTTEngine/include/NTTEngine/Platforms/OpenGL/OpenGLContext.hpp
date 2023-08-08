#pragma once

#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <NTTEngine/Renderer/Renderer.hpp>


namespace ntt
{
    class OpenGLContext: public GraphicsContext
    {
        public:
            OpenGLContext(GLFWwindow* win);
            ~OpenGLContext();

            void Init() override;
            void SwapBuffer() override;

        private:
            GLFWwindow* window_;
    }; 
} // namespace ntt
