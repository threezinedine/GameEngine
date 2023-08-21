#include "UART/UART.hpp"


UARTCom* UARTCom::instance_ = nullptr;


void UARTCom::Initialize(std::string com, int baudrate)
{
    instance_ = new UARTCom(com, baudrate);
}

void UARTCom::StartConnectionSta()
{
    instance_->StartConnection();
}

void UARTCom::FinishConnectionSta()
{
    instance_->StopConnection();
}

void UARTCom::SubmitCommand(std::shared_ptr<UARTCommand> command)
{
    instance_->RunCommand(command);
}

void UARTCom::Release()
{
    if (instance_ != nullptr)
    {
        delete instance_;
    }
}


static DWORD  GetBaudRate(int baudrate)
{
    switch (baudrate)
    {
        case 115200:
            return CBR_115200;
        case 9600:
            return CBR_9600;
    }
    return CBR_115200;
}


UARTCom::UARTCom(std::string com, int baudrate)
    : com_(com), baudrate_(baudrate), state_(IdleState), workingState_(Working_Idle),
        isConnected_(false, false, false), status_(UART_NONE)
{
    selectableVector_ = std::make_shared<ntt::ImGuiSelectableVector<std::string>>(
        std::vector<std::pair<std::string, std::string>>
        {
            { std::string("COM7"), std::string("COM7") },
            { std::string("COM6"), std::string("COM6") },
            { std::string("COM5"), std::string("COM5") },
        },
        [this]() -> std::string 
        {
            return com_;
        },
        [this](std::string value)
        {
            com_ = value; 
        }
    );
}

UARTCom::~UARTCom()
{

}

ConnectionStatus UARTCom::Connect()
{
    hCom_ = CreateFile(com_.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hCom_ == INVALID_HANDLE_VALUE) {
        return UART_FAIL_TO_OPEN;
    }

    serialParam_.DCBlength = sizeof(serialParam_);
    if (!GetCommState(hCom_, &serialParam_)) {
        CloseHandle(hCom_);
        return UART_FAIL_TO_SETTING;
    }

    serialParam_.BaudRate = GetBaudRate(baudrate_);   // Baud rate
    serialParam_.ByteSize = 8;           // Data bits
    serialParam_.StopBits = ONESTOPBIT;  // Stop bits
    serialParam_.Parity = NOPARITY;      // Parity

    timeOut_.ReadIntervalTimeout = 50;
    timeOut_.ReadTotalTimeoutConstant = 50;
    timeOut_.ReadTotalTimeoutMultiplier = 10;
    timeOut_.WriteTotalTimeoutConstant = 50;
    timeOut_.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hCom_, &timeOut_);
    if (!SetCommTimeouts(hCom_, &timeOut_)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_ACCESS_DENIED:
                NTT_APPLICATION_DEBUG("Access denied. Make sure the port is not already open.");
                break;
            case ERROR_FILE_NOT_FOUND:
                NTT_APPLICATION_DEBUG("Port not found. Check the port name.");
                break;
            default:
                NTT_APPLICATION_DEBUG("Failed to set UART timeouts. Error code: {}", errorCode);
                break;
        }
        CloseHandle(hCom_);
        return UART_FAIL_TO_TIME_SETTING;
    }
    
    return UART_OK;
}

void UARTCom::Disconnect()
{
    CloseHandle(hCom_);
}

ConnectionStatus UARTCom::SendData(std::vector<unsigned char> data, bool needRes)
{
    unsigned char* sendArray = new unsigned char[data.size()];
    for (int i=0; i<data.size(); i++)
    {
        sendArray[i] = data[i];
    }

    DWORD bytesWritten;

    if (!WriteFile(hCom_, sendArray, data.size() * sizeof(char), &bytesWritten, NULL)) {
        Disconnect();
        return UART_FAIL_TO_SEND_DATA;
    }

    if (needRes)
    {
        if (!ReadFile(hCom_, buffer_, sizeof(buffer_), &bytesRead, NULL)) {
            std::cerr << "Failed to read response" << std::endl;
            Disconnect();
            return UART_FAIL_TO_RECEIVE_DATA;
        }
    }

    delete sendArray;

    return UART_OK;
}



ConnectionStatus UARTCom::ChangeCoil(unsigned char coilAddress, bool active)
{
    if (active)
    {
        return SendData({ 0x00, address_, 0x01, coilAddress, 0x00, 0x01, 0xff });
    }
    else 
    {
        return SendData({ 0x00, address_, 0x01, coilAddress, 0x00, 0x00, 0xff });
    }
}
ConnectionStatus UARTCom::ChangeRegister(unsigned char registerAddress, Register value)
{
    return SendData({ 0x00, address_, 0x02, registerAddress, value.buffer[0], value.buffer[1], 0xff });
}

ConnectionStatus UARTCom::ChangeFloat(unsigned char firstRegisterAddress, 
        unsigned char secondRegisterAddress, float value)
{
    ConnectionStatus status1 = UART_NONE, status2 = UART_NONE;
    Float32 unionValue;
    unionValue.value = value;

    status1 = ChangeRegister(firstRegisterAddress, unionValue.buffer[0]);
    if (status1 != UART_OK) return status1;

    status2 = ChangeRegister(secondRegisterAddress, unionValue.buffer[1]);
    if (status2 != UART_OK) return status2;

    return UART_OK;
}

ConnectionStatus UARTCom::GetCoil(unsigned char coilAdress, bool* active)
{
    auto status = SendData({ 0x00, address_, 0x03, coilAdress, 0x00, 0x00, 0xff }, true);    
    *active = buffer_[5];
    return status;
}

ConnectionStatus UARTCom::GetRegister(unsigned char registerAddress, Register* value)
{
    auto status = SendData({ 0x00, address_, 0x04, registerAddress, 0x00, 0x00, 0xff }, true);
    value->buffer[0] = buffer_[4];
    value->buffer[1] = buffer_[5];
    return status;
}

ConnectionStatus UARTCom::GetFloat(unsigned char firstRegisterAddress, unsigned char secondRegisterAddress, float* value)
{
    Float32 unionValue;
    auto status = GetRegister(firstRegisterAddress, &(unionValue.buffer[0]));
    if (status != UART_OK) return status;

    auto status2 = GetRegister(secondRegisterAddress, &(unionValue.buffer[1]));
    if (status2 != UART_OK) return status2;

    *value = unionValue.value;
    return UART_OK;
}

void UARTCom::OnInitImpl()
{

}

void UARTCom::OnUpdateImpl()
{
    isConnected_.Bind();
    switch (state_)
    {
        case IdleState:
            if (isConnected_.GetValue())
            {
                state_ = ConnectingState;
            }
            break;
        case ConnectingState:
            status_ = Connect();
            if (status_ == UART_OK)
            {
                state_ = WorkingState;
                workingState_ = Working_Idle;
                while(!commands_.empty()) commands_.pop();
            }
            if (status_ != UART_OK)
            {
                state_ = IdleState;
                *(isConnected_.GetPointer()) = false;
            }
            break;
        case WorkingState:
            RunWorkingState();
            if (!isConnected_.GetValue())
            {
                Disconnect();
                state_ = IdleState;
            }
            break;
    }
    isConnected_.UnBind();
}

void UARTCom::RunWorkingState()
{
    switch (workingState_)
    {
        case Working_Idle:
            if (!commands_.empty())
            {
                workingState_ = Working_Run;
            }
            break;
        case Working_Run:
            commands_.front()->OnRun();
            commands_.pop();
            if (commands_.empty())
            {
                workingState_ = Working_Idle;
            }
            break; 
    }
}


void UARTCom::OnReleaseImpl()
{
    if (isConnected_.GetValue())
    {
        Disconnect();
    }
}

void UARTCom::StartConnection()
{
    isConnected_.Bind();
    *(isConnected_.GetPointer()) = true;
    isConnected_.UnBind();
}


void UARTCom::StopConnection()
{
    isConnected_.Bind();
    *(isConnected_.GetPointer()) = false;
    isConnected_.UnBind();
}

void UARTCom::RunCommand(std::shared_ptr<UARTCommand> command)
{
    commands_.push(command);
}

void UARTCom::OnImGuiRender()
{
    ImGui::Text("Select Com");
    selectableVector_->OnImGuiRender();
    ImGui::Separator();
}