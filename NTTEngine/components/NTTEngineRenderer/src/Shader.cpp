#include "NTTEngineRenderer/NTTEngineRenderer.hpp"
#include <fstream>


namespace ntt
{
    const std::string SHADER_KEY = "#shader";

    Shader::Shader(const std::string& filePath, 
                    const std::string& vertexKey, 
                    const std::string& fragmentKey
        )
        : filePath_(filePath), rendererId_(0)
    {
        ParseShader(filePath);

        rendererId_ = CreateShader(
            shaderPrograms_[vertexKey], 
            shaderPrograms_[fragmentKey]
        );

    } 

    std::string Shader::GetCurrentFolder()
    {
        std::string filePath = std::string(__FILE__);
        size_t found = filePath.find_last_of("/\\"); // Find the last path separator
        if (found != std::string::npos) {
            return filePath.substr(0, found); // Extract the directory path
        }
        return "";
    }

    void Shader::ParseShader(const std::string& file)
    {
        std::ifstream stream(GetCurrentFolder() + "/" + file);

        std::string source;
        std::string line;
        while (getline(stream, line))
        {
            source += line + "\n";
        }

        GetShaderMap(source);
    }

    void Shader::GetShaderMap(const std::string& shaderCode)
    {
        std::string mutableShaderCode = shaderCode;

        size_t pos = 0;
        while ((pos = mutableShaderCode.find(SHADER_KEY)) != std::string::npos) {
            mutableShaderCode.erase(0, pos + SHADER_KEY.length());

            size_t shaderTypeEnd = mutableShaderCode.find_first_of('\n');
            std::string shaderType = mutableShaderCode.substr(0, shaderTypeEnd);

            mutableShaderCode.erase(0, shaderTypeEnd + 1);

            size_t shaderEnd = mutableShaderCode.find(SHADER_KEY, 0);
            const std::string shaderContent = mutableShaderCode.substr(0, shaderEnd);

            shaderPrograms_[shaderType.substr(1)] = shaderContent;
        }
    }

} // namespace ntt
