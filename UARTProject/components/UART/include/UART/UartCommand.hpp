#pragma once


class UARTCom;

class UARTCommand
{
    public:
        UARTCommand()
        {

        }
        virtual ~UARTCommand() = default;

        void OnRun()
        {
            OnRunImpl();
        }

    protected:
        virtual void OnRunImpl() = 0;
        
    private:
};