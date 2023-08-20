#pragma once
#include <GL/glew.h>
#include <glfw/glfw3.h>


namespace ntt
{
    class GraphicsContext
    {
        public:
            GraphicsContext(GLFWwindow* window);
            ~GraphicsContext();
            virtual void Init();
            virtual void SwapBuffer();

        private:
            GLFWwindow* window_;
    }; 
} // namespace ntt
