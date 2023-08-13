#pragma once
#include <string>


namespace ntt
{
    class IFileSystem
    {
        public:
            virtual std::string Read() = 0;
            virtual void Save(std::string value) = 0;
    }; 
} // namespace ntt
