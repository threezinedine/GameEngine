#include <iostream>
#include <fstream>
#include "RealFileSystem.hpp"


namespace ntt
{
    RealFileSystem::RealFileSystem(std::string filePath) 
        : filePath_(filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open()) 
        {
            std::ofstream newFile(filePath, std::ios::app);
            if (newFile.is_open()) 
            {
                newFile << "{}";
                newFile.close();
            } 
        }
    }

    RealFileSystem::~RealFileSystem()
    {

    }

    std::string RealFileSystem::Read()
    {
        std::ifstream input(filePath_);
        std::string content = "";
        
        if (!input) {
            std::cerr << "Failed to open file for reading." << std::endl;
            return "";
        }

        std::string line;
        while (std::getline(input, line)) {
            content += line + "\n"; // Append the line to the content string
        }

        input.close();
        return content;
    }

    void RealFileSystem::Save(std::string data)
    {
        std::ofstream output(filePath_);
        output << data;
        output.close();
    }
} // namespace ntt
