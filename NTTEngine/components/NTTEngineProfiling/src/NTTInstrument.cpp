#include "NTTEngineProfiling/PreInclude.hpp"


namespace ntt
{
    NTTInstrument* NTTInstrument::instance_ = nullptr;

    NTTInstrument::NTTInstrument(const char* fileName)
        : file_(fileName, std::ios::trunc)
    {
        Start();
    } 

    NTTInstrument::~NTTInstrument()
    {
        Stop();
    }

    void NTTInstrument::StartSession(const char* fileName)
    {
        if (instance_ != nullptr)
        {
            delete instance_;
        }

        instance_ = new NTTInstrument(fileName);
    }

    void NTTInstrument::WriteEvent(NTTInstrumentEventData event)
    {
        if (instance_ != nullptr)
        {
            instance_->AddEvent(event);
        }
    }

    void NTTInstrument::EndSession()
    {
        delete instance_;
        instance_ = nullptr;
    }

    void NTTInstrument::Start()
    {
        file_ << "[\n";
    }

    void NTTInstrument::AddEvent(NTTInstrumentEventData event)
    {
        if (!noData_)
        {
            file_ << ",\n";
        }
        noData_ = false;

        file_ << "\t{\n";
        file_ << "\t\t\"name\": \"" << event.name << "\",\n";
        file_ << "\t\t\"cat\": \"function\",\n";
        file_ << "\t\t\"pid\": 0,\n";
        file_ << "\t\t\"tid\": 0,\n";
        file_ << "\t\t\"ph\": \"" << "X" << "\",\n";
        file_ << "\t\t\"dur\": \"" << (event.stopTime - event.startTime) << "\",\n";
        file_ << "\t\t\"ts\": \"" << event.startTime << "\"\n";
        file_ << "\t}";
        file_.flush();
    }

    void NTTInstrument::Stop()
    {
        file_ << "\n]";
        file_.close();
    }
} // namespace ntt
