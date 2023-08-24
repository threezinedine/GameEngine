#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/RendererAPI.hpp"
#include "OpenGLPreInclude.hpp"


namespace ntt
{
    void RendererAPI::Init()
    {
        PROFILE_SCOPE();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

} // namespace ntt
