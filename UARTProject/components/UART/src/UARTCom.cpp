#include "UART/UART.hpp"
#include <sstream>


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

    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./uart-application-code-config.json")
    );

    startByte_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x00, storage_, "START_BYTE");

    stopByte_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0xff, storage_, "STOP_BYTE");

    setOneCoilFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x01, storage_, "SET_ONE_COIL_FUNC");
    setMulCoilsFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x02, storage_, "SET_MUL_COILS_FUNC");
    setOneRegisterFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x03, storage_, "SET_ONE_REGISTER_FUNC");
    setMulRegistersFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x04, storage_, "SET_MUL_REGISTERS_FUNC");

    readOneCoilFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x05, storage_, "READ_ONE_COIL_FUNC");
    readMulCoilsFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x06, storage_, "READ_MUL_COILS_FUNC");
    readOneRegisterFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x07, storage_, "READ_ONE_REGISTER_FUNC");
    readMulRegistersFuncCode_ = std::make_shared<ntt::ThreadValue<unsigned char>>(0x08, storage_, "READ_MUL_REGISTERS_FUNC");
}

UARTCom::~UARTCom()
{
    startByte_->Save();
    stopByte_->Save();

    setOneCoilFuncCode_->Save();
    setMulCoilsFuncCode_->Save();
    setOneRegisterFuncCode_->Save();
    setMulRegistersFuncCode_->Save();

    readOneCoilFuncCode_->Save();
    readMulCoilsFuncCode_->Save();
    readOneRegisterFuncCode_->Save();
    readMulRegistersFuncCode_->Save();

    storage_->Save();
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
    int size = data.size() + 4;
    unsigned char index = 0;
    unsigned char dataIndex = 0;
    unsigned char* sendArray = new unsigned char[size];

    while (index < size)
    {
        if (index == 0)
        {
            sendArray[index] = startByte_->GetValue();
        }
        else if (index == 1)
        {
            sendArray[index] = address_;
        }
        else if (index == size - 1)
        {
            sendArray[index] = stopByte_->GetValue();
        }
        else if (index == 2)
        {
            sendArray[index] = size;
        }
        else 
        {
            sendArray[index] = data[dataIndex++];
        }
        index++;
    }

    DWORD bytesWritten;

    std::cout << "Sending" << std::endl;
    for (int i=0; i<sendArray[2]; i++)
    {
        std::cout << " 0x";
        std::cout << std::hex << std::setw(2)
            << std::setfill('0') << static_cast<unsigned int>(sendArray[i]);
    }
    std::cout << std::endl;

    if (!WriteFile(hCom_, sendArray, sendArray[2], &bytesWritten, NULL)) {
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
        std::cout << "Receive" << std::endl;
        for (int i=0; i<buffer_[2]; i++)
        {
            std::cout << " 0x";
            std::cout << std::hex << std::setw(2)
                << std::setfill('0') << static_cast<unsigned int>(buffer_[i]);
        }
        std::cout << std::endl;
    }

    delete sendArray;

    return UART_OK;
}



ConnectionStatus UARTCom::ChangeCoil(unsigned char coilAddress, bool active)
{
    if (active)
    {
        return SendData({ setOneCoilFuncCode_->GetValue(), 
                            coilAddress, 0x01 }, true);
    }
    else 
    {
        return SendData({ setOneCoilFuncCode_->GetValue(), 
                            coilAddress, 0x00 }, true);
    }
}
ConnectionStatus UARTCom::ChangeRegister(unsigned char registerAddress, Register value)
{
    return SendData({ setOneRegisterFuncCode_->GetValue(),
                            registerAddress, 
                            value.buffer[0], 
                            value.buffer[1] });
}

ConnectionStatus UARTCom::ChangeRegisters(unsigned char startAddr, 
                unsigned char stopAddr, std::vector<Register> data)
{
    std::vector<uint8_t> query 
    {
        setMulRegistersFuncCode_->GetValue(),
        startAddr,
        stopAddr,
    };

    for (auto registerInfo: data)
    {
        query.push_back(registerInfo.buffer[0]);
        query.push_back(registerInfo.buffer[1]);
    }

    return SendData(query);
}

ConnectionStatus UARTCom::ChangeFloat(unsigned char firstRegisterAddress, float value)
{
    Float32 unionValue;
    unionValue.value = value;

    return ChangeRegisters(firstRegisterAddress, firstRegisterAddress + 1, 
                                { unionValue.buffer[0], unionValue.buffer[1] });
}

ConnectionStatus UARTCom::GetCoil(unsigned char coilAdress, bool* active)
{
    auto status = SendData({ readOneCoilFuncCode_->GetValue(), coilAdress }, true);    
    if (status == UART_OK && buffer_[4] == 1)
    {
        *active = buffer_[6];
    }
    return status;
}

ConnectionStatus UARTCom::GetRegisters(unsigned char startAddr, std::vector<Register*> values)
{
    unsigned char stopAddr = startAddr + values.size();
    auto status = SendData({ readMulRegistersFuncCode_->GetValue(), 
                            startAddr, stopAddr }, true);
                
    if (status == UART_OK && buffer_[4] == 1)
    {
        for (int i=0; i<values.size(); i++)
        {
            values[i]->buffer[0] = buffer_[7 + 2*i];    
            values[i]->buffer[1] = buffer_[8 + 2*i];    
        }
    }
    return status;
}

ConnectionStatus UARTCom::GetRegister(unsigned char registerAddress, Register* value)
{
    auto status = SendData({ readOneRegisterFuncCode_->GetValue(), registerAddress }, true);
    if (status == UART_OK && buffer_[4] == 1)
    {
        value->buffer[0] = buffer_[6];
        value->buffer[1] = buffer_[7];
    }
    return status;
}

ConnectionStatus UARTCom::GetFloat(unsigned char firstRegisterAddress, float* value)
{
    Float32 unionValue;
    auto status = GetRegisters(firstRegisterAddress, { &unionValue.buffer[0], &unionValue.buffer[1] });

    *value = unionValue.value;
    return status;
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

static std::string ToHexString(unsigned char value) {
    std::ostringstream stream;
    stream << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
    return stream.str();
}

static unsigned char StringToHex(char* hexString)
{
    int intValue = std::stoi(hexString, nullptr, 16);
    return (unsigned int)intValue;
}

void UARTCom::OnImGuiRender()
{
    ImGui::Text("Select Com");
    selectableVector_->OnImGuiRender();
    ImGui::Separator();
    std::string addressString = std::string("Current Device Address: ") + ToHexString(address_);
    ImGui::Text(addressString.c_str());
    static char address[3];
    ImGui::InputText("Device Address", address, 3, ImGuiInputTextFlags_CharsHexadecimal);
    if (ImGui::Button("Setting"))
    {
        SetAddress(StringToHex(address));
    }
    ImGui::Separator();
    if (ImGui::Button("Connect"))
    {
        StartConnection();
    }
    ImGui::SameLine();
    if (ImGui::Button("Disconnect"))
    {
        StopConnection();
    }
    ImGui::Separator();
}