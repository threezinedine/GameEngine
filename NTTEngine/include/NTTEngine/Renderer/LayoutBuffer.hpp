#pragma once

#include <string>


namespace ntt
{
    enum LayoutType
    {
        Float,
        Float2,
        Float3,
        Float4,
        Mat2,
        Mat3,
        Mat4,
        Bool,
    };

    unsigned int GetTypeNum(LayoutType type);
    unsigned int GetTypeSize(LayoutType type);

    struct LayoutBuffer
    {
        LayoutType type;
        std::string name;
        unsigned int num;
        bool normalized;
        unsigned int size;
        unsigned int offset; 

        LayoutBuffer(LayoutType type, const std::string& name, bool normalized = false)
            : type(type), name(name), num(GetTypeNum(type)), 
                normalized(normalized), size(GetTypeSize(type)), offset(0)
        {

        }
    };
} // namespace ntt
