#pragma once
#include <string>
#include "PreInclude.hpp"
#include <fstream>


namespace ntt
{
    struct NTTInstrumentEventData
    {
        const char* name;
        long long startTime;
        long long stopTime;
        const char* category;
    };

    class NTTInstrument
    {
        public:
            NTTInstrument(const char* fileName);
            ~NTTInstrument();

            static void StartSession(const char* fileName);
            static void WriteEvent(NTTInstrumentEventData event);
            static void EndSession();

            void Start();
            void AddEvent(NTTInstrumentEventData event);
            void Stop();

        private:
            std::ofstream file_;
            bool noData_ = true;

            void AddJsonEvent(const char* name, 
                    int64_t time, const char* ph);

            static NTTInstrument* instance_;
    }; 
} // namespace ntt

