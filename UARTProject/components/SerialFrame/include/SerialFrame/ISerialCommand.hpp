#pragma once
#include "SerialFrameResultStatus.hpp"

class SerialFrameManager;

class ISerialCommand
{
    public:
        virtual SerialFrameResult OnRun(SerialFrameManager* manager) = 0;
};