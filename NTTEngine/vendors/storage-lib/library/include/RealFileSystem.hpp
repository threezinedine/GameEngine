#pragma once
#include <string>
#include <fstream>
#include "IFileSystem.hpp"


namespace ntt
{
    class RealFileSystem: public IFileSystem
    {
        public:
            RealFileSystem(std::string filePath);
            ~RealFileSystem();

            std::string Read() override;
            void Save(std::string data) override;

        private:
            std::string filePath_;
    };
} // namespace ntt
