#include <NTTEngine/Renderer/LayoutBuffer.hpp>


namespace ntt
{
    unsigned int GetTypeNum(LayoutType type)
    {
        switch (type)
        {
            case Float:
                return 1;
            case Float2:
                return 2;
            case Float3:
                return 3;
            case Float4:
                return 4;
            case Mat2:
                return 2 * 2;
            case Mat3:
                return 3 * 3;
            case Mat4:
                return 4 * 4;
            case Bool:
                return 1;
        }
        return 0;
    }

    unsigned int GetTypeSize(LayoutType type)
    {
        switch (type)
        {
            case Float:
            case Float2:
            case Float3:
            case Float4:
            case Mat2:
            case Mat3:
            case Mat4:
                return sizeof(float) * GetTypeNum(type);
            case Bool:
                return sizeof(bool) * GetTypeNum(type);
        }
        return 0;
    }
} // namespace ntt
