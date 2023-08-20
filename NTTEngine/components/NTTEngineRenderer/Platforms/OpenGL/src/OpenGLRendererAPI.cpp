#include "GL/glew.h"
#include "glfw/glfw3.h"
#include "NTTEngineCore/NTTEngineCore.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    void RendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

} // namespace ntt
