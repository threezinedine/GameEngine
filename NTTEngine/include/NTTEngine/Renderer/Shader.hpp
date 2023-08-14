#pragma once
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>


namespace ntt
{
    class Shader
    {
        public:
            Shader(const std::string& filePath, 
                    const std::string& vertexKey, 
                    const std::string& fragmentKey);
            ~Shader();

            void Bind() const;
            void UnBind() const;

            void SetUniform1i(const std::string& locationName, int value);
            void SetUniform4f(const std::string& locationName, float f0, float f1, float f2, float f3);
            void SetUniform3f(const std::string& locationName, float f0, float f1, float f2);
            void SetUniform3f(const std::string& locationName, glm::vec3 vec);
            void SetUniformMat4f(const std::string& locationName, glm::mat4& matrix);
        private:
            const std::string& filePath_;
            unsigned int rendererId_;
            std::unordered_map<std::string, std::string> shaderPrograms_;
            std::unordered_map<std::string, int> uniforms_;

            std::string GetCurrentFolder();
            unsigned int GetLocation(const std::string& locationName);
            void ParseShader(const std::string& filePath);
            unsigned int CompileShader(const std::string& source, unsigned int type);
            unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
            void GetShaderMap(const std::string& shaderCode);
    }; 
} // namespace ntt
