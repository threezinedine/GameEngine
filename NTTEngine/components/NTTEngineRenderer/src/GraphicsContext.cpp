#include "NTTEngineLog/NTTEngineLog.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    GraphicsContext::~GraphicsContext()
    {
        NTT_ENGINE_DEBUG("Delete GraphicsContext");
    }
} // namespace ntt
