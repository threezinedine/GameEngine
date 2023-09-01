#include <imgui.h>
#include <string>
#include "SerialUART/UARTConnection.hpp"

static DWORD  GetBaudRate(int);
// static void GetLPCSTR(const char*, LPCSTR*);
// static void GetLPCSTR(std::string, LPCSTR*);

UARTConnection::UARTConnection(const std::string& name, const char* comPort, int baudrate)
    : name_(name), comPort_(std::string(comPort)), isConnected_(false)
{
    selectableVectorCom_ = std::make_shared<ntt::ImGuiSelectableVector<std::string>>(
        std::vector<std::pair<std::string, std::string>>
        {
            { std::string("COM7"), std::string("COM7") },
            { std::string("COM6"), std::string("COM6") },
            { std::string("COM5"), std::string("COM5") },
        },
        [this]() -> std::string 
        {
            return comPort_;
        },
        [this](std::string value)
        {
            comPort_ = value; 
        }
    );

    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./serial-uart-connection-code-config.json")
    );

    baudrate_ = std::make_shared<ntt::ThreadValue<int>>(
        baudrate, storage_, "baudrate"
    );

    selectableVectorBaudrate_ = std::make_shared<ntt::ImGuiSelectableVector<int>>(
        std::vector<std::pair<std::string, int>>
        {
            { std::string("115200"), 115200 },
            { std::string("9600"), 9600 },
            // { std::string("COM5"), std::string("COM5") },
        },
        [this]() -> int
        {
            return baudrate_->GetValue();
        },
        [this](int value)
        {
            *(baudrate_->GetPointer()) = value; 
        }
    );

}


UARTConnection::~UARTConnection()
{
    baudrate_->Save();

    storage_->Save();

    if (isConnected_.GetValue())
    {
        Disconnect();
    }
}

bool UARTConnection::IsConnected()
{
    bool result = false;
    isConnected_.Bind();
    result = isConnected_.GetValue();
    isConnected_.UnBind();
    return result; 
}

SerialFrameResult UARTConnection::Connect()
{
    hCom_ = CreateFile(comPort_.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hCom_ == INVALID_HANDLE_VALUE) {
        return { SERIAL_RESULT_FAIL_TO_SETTING, 0 };
    }

    serialParam_.DCBlength = sizeof(serialParam_);
    if (!GetCommState(hCom_, &serialParam_)) {
        CloseHandle(hCom_);
        return { SERIAL_RESULT_FAIL_TO_SETTING, 0 };
    }

    serialParam_.BaudRate = GetBaudRate(baudrate_->GetValue());   // Baud rate
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
        return { SERIAL_RESULT_FAIL_TO_SETTING, 0 };
    }

    isConnected_.Bind(); 
    *(isConnected_.GetPointer()) = true;
    isConnected_.UnBind(); 
    return { SERIAL_RESULT_OK, 0 };
}

void UARTConnection::Disconnect()
{
    CloseHandle(hCom_);
    isConnected_.Bind(); 
    *(isConnected_.GetPointer()) = false;
    isConnected_.UnBind(); 
}


std::vector<uint8_t> UARTConnection::SendRequets(std::vector<uint8_t> request, bool needRes)
{
    uint8_t* sendData = new uint8_t[request.size()];
    DWORD bytesWritten;

    for (int i=0; i<request.size(); i++)
    {
        sendData[i] = request[i];
        std::cout << "0x" << std::setw(2) << std::setfill('0') 
                << std::hex << static_cast<unsigned int>(request[i]) << " ";
    }
    std::cout << std::endl;

    if (!WriteFile(hCom_, sendData, sendData[2], &bytesWritten, NULL)) {
        Disconnect();
        return {  };
    }

    if (needRes)
    {
        std::vector<uint8_t> response;

        if (!ReadFile(hCom_, buffer_, sizeof(buffer_), &bytesRead, NULL)) {
            std::cerr << "Failed to read response" << std::endl;
            Disconnect();
            return {  };
        }
        std::cout << "Receive" << std::endl;
        for (int i=0; i<buffer_[2]; i++)
        {
            std::cout << " 0x";
            std::cout << std::hex << std::setw(2)
                << std::setfill('0') << static_cast<unsigned int>(buffer_[i]);
            response.push_back(buffer_[i]);
        }
        std::cout << std::endl;

        return response;
    }

    delete sendData;
    return {  };
}

void UARTConnection::OnImGuiRender(ntt::Timestep ts) 
{
    ImGui::Text("Select Com");
    selectableVectorCom_->OnImGuiRender();
    ImGui::Text("Select baudrate");
    selectableVectorBaudrate_->OnImGuiRender();
    ImGui::Separator();
    if (ImGui::Button("Connect"))
    {
        Connect();
    }
    ImGui::SameLine();
    if (ImGui::Button("Disconnect"))
    {
        Disconnect();
    }
    ImGui::Separator();
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

// static LPCWSTR GetLPCSTR(const char* narrowStr, LPCSTR* wideStr)
// {
//     int wideStrLength = MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, nullptr, 0);
//     if (wideStrLength == 0) {
//         std::cerr << "Error calculating wide string length" << std::endl;
//     }

//     WCHAR* wideStr = new WCHAR[wideStrLength];
//     if (!MultiByteToWideChar(CP_UTF8, 0, narrowStr, -1, wideStr, wideStrLength)) {
//         std::cerr << "Error converting to wide string" << std::endl;
//         delete[] wideStr;
//     }

//     return wideStr;
// }

// static LPCWSTR GetLPCSTR(std::string narrowStr, LPCSTR* wideStr)
// {
//     return GetLPCWSTR(narrowStr.c_str(), wideStr);
// }
