#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/FrameBuffer.hpp"


namespace ntt
{
    FrameBuffer::FrameBuffer(int width, int height, int format)
        : width_(width), height_(height), format_(format)
    {
        Invalid();
    }

} // namespace ntt
