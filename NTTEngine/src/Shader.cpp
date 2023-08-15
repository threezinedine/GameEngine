#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <fstream>
#include <NTTEngine/Core.hpp>
#include <NTTEngine/Renderer/Shader.hpp>


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

    Shader::~Shader()
    {
        glDeleteProgram(rendererId_);
    }

    void Shader::Bind() const 
    {
        GL_CALL(glUseProgram(rendererId_));
    }

    void Shader::UnBind() const
    {
        GL_CALL(glUseProgram(0));
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

    unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        GL_CALL(glShaderSource(id, 1, &src, nullptr));
        GL_CALL(glCompileShader(id));

        int success; 
        GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

        if (success == GL_FALSE)
        {
            int length;
            GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* log = (char*)alloca(length * sizeof(char));

            GL_CALL(glGetShaderInfoLog(id, length, &length, log));

            NTT_ENGINE_ERROR("Error when compile {} -- Error: {}", 
                (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader"),
                log
            );
            GL_CALL(glDeleteShader(id));
            return 0;
        }

        return id;
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GL_CALL(unsigned int program = glCreateProgram());

        unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
        unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

        GL_CALL(glAttachShader(program, vs));
        GL_CALL(glAttachShader(program, fs));
        GL_CALL(glLinkProgram(program));
        GL_CALL(glValidateProgram(program));

        GL_CALL(glDeleteShader(vs));
        GL_CALL(glDeleteShader(fs));

        return program;
    }

    unsigned int Shader::GetLocation(const std::string& locationName)
    {
        if (uniforms_.find(locationName) != uniforms_.end())
        {
            return uniforms_[locationName];
        }

        GL_CALL(unsigned int location = glGetUniformLocation(rendererId_, locationName.c_str()));

        uniforms_[locationName] = location;

        return location;
    }

    void Shader::SetUniform1i(const std::string& locationName, int value)
    {
        auto location = GetLocation(locationName);

        if (location != -1)
        {
            Bind();
            GL_CALL(glUniform1i(location, value));
        }
    }

    void Shader::SetUniform4f(const std::string& locationName, float f0, float f1, float f2, float f3)
    {
        auto location = GetLocation(locationName);

        if (location != -1)
        {
            Bind();
            GL_CALL(glUniform4f(location, f0, f1, f2, f3));
        }
    }

    void Shader::SetUniform3f(const std::string& locationName, float f0, float f1, float f2)
    {
        auto location = GetLocation(locationName);

        if (location != -1)
        {
            Bind();
            GL_CALL(glUniform3f(location, f0, f1, f2));
        }
    }

    void Shader::SetUniform3f(const std::string& locationName, glm::vec3 vec)
    {
        auto location = GetLocation(locationName);

        if (location != -1)
        {
            Bind();
            GL_CALL(glUniform3f(location, vec.x, vec.y, vec.z));
        }
    }

    void Shader::SetUniformMat4f(const std::string& locationName, glm::mat4& matrix)
    {
        auto location = GetLocation(locationName);

        if (location != -1)
        {
            Bind();
            GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
        }
    } 
} // namespace ntt
