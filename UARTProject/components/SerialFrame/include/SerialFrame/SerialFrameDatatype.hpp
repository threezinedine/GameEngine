#pragma once
#include <cstdint>


union Coil
{
    bool value;
    uint8_t buffer;
};

union Register
{
    uint8_t buffer[2];
};

union Int16
{
    uint16_t value;
    Register buffer;
};


union Int32
{
    uint32_t value;
    Register buffer[2];
};


union Float32
{
    float value;
    Register buffer[2];
};