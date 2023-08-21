#pragma once


class UARTCom;

class UARTCommand
{
    public:
        UARTCommand(UARTCom& com)
            : com_(com)
        {

        }
        virtual ~UARTCommand() = default;

        void OnRun()
        {
            OnRunImpl(com_);
        }

    protected:
        virtual void OnRunImpl(UARTCom& com) = 0;
        
    private:
        UARTCom& com_;
};