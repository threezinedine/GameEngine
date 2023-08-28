#pragma once
#include <cstdint>
#include "ISerialCommand.hpp"
#include "SerialFrameResultStatus.hpp"


class SerialCommandChangeBool: public ISerialCommand
{
    public:
        SerialCommandChangeBool(uint8_t addr, bool active);

        SerialFrameResult OnRun(SerialFrameManager* manager) override;

    private:
        uint8_t addr_;
        bool active_;
};