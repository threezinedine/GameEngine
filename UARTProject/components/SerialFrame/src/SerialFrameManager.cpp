#include "SerialFrame/PreInclude.hpp"

#include "SerialFrame/IConnection.hpp"
#include "SerialFrame/SerialFrame.hpp"
#include "SerialFrame/ISerialCommand.hpp"


SerialFrameManager* SerialFrameManager::instance_ = nullptr;


SerialFrameManager::SerialFrameManager(std::unique_ptr<IConnection> connection)
    : connection_(std::move(connection)), state_(IdleState), workingState_(Working_Idle)
{
    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./serial-code-config.json")
    );

    startByte_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x00, storage_, "START_BYTE");

    stopByte_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0xff, storage_, "STOP_BYTE");
    address_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x34, storage_, "ADDRESS");
}

SerialFrameManager::~SerialFrameManager()
{
    startByte_->Save();
    stopByte_->Save();
    address_->Save();

    storage_->Save();

    if (connection_->IsConnected())
    {
        connection_->Disconnect();
    }
}

void SerialFrameManager::SubmitCommandInstance(std::shared_ptr<ISerialCommand> command)
{
    commandQueue_.push(command);
}

void SerialFrameManager::OnImGuiRenderInstance(ntt::Timestep ts)
{
    connection_->OnImGuiRender(ts);
}


SerialFrameResult SerialFrameManager::Connect()
{
    return connection_->Connect();
}

SerialFrameResult SerialFrameManager::SendData(std::vector<uint8_t> data, std::vector<uint8_t>& res)
{
    std::vector<uint8_t> sendData(data);
    sendData.insert(sendData.begin(), startByte_->GetValue());
    sendData.insert(sendData.begin() + 1, address_->GetValue());
    sendData.push_back(stopByte_->GetValue());
    sendData.insert(sendData.begin() + 2, sendData.size() + 1);

    res = connection_->SendRequets(sendData, true);

    if (res[3])
    {
        return { SERIAL_RESULT_OK, 0 };
    }
    else 
    {
        return { SERIAL_RESULT_RESPONSE_ERROR, res[5] };
    }
}

void SerialFrameManager::Disconnect()
{
    connection_->Disconnect();
}


void SerialFrameManager::OnInitImpl()
{

}

void SerialFrameManager::OnUpdateImpl()
{
    SerialFrameResult result;
    switch (state_)
    {
        case IdleState:
            if (connection_->IsConnected())
            {
                state_ = WorkingState;
                workingState_ = Working_Idle;
                while(!commandQueue_.empty()) commandQueue_.pop();
            }
            break;
        case WorkingState:
            RunWorkingState();
            if (!connection_->IsConnected())
            {
                state_ = IdleState;
            }
            break;
    }
}

void SerialFrameManager::RunWorkingState()
{
    switch (workingState_)
    {
        case Working_Idle:
            if (!commandQueue_.empty())
            {
                workingState_ = Working_Run;
            }
            break;
        case Working_Run:
            commandQueue_.front()->OnRun(this);
            commandQueue_.pop();
            if (commandQueue_.empty())
            {
                workingState_ = Working_Idle;
            }
            break; 
    }
}

void SerialFrameManager::OnReleaseImpl()
{
    if (connection_->IsConnected())
    {
        connection_->Disconnect();
    }
}