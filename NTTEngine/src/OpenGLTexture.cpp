#include <opencv2/opencv.hpp>
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <NTTEngine/Platforms/OpenGL/OpenGLTexture.hpp>
#include <NTTEngine/NTTEngine.hpp>


namespace ntt
{
    OpenGLTexture2D::OpenGLTexture2D(std::string file)
    {
        cv::Mat image = cv::imread(file);

        GLenum internalFormat = 0, dataFormat = 0;

        if (image.channels() == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (image.channels() == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        NTT_ENGINE_DEBUG("Channel: {}", image.channels());

        GL_CALL(glGenTextures(1, &id_));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));

        // GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        // GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, image.cols, image.rows, 
                        0, dataFormat, GL_UNSIGNED_BYTE, image.data));
    }  

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        GL_CALL(glDeleteTextures(1, &id_));
    }

    void OpenGLTexture2D::Bind(uint32_t slot)
    {
        // glBindTextureUnit(slot, id_);
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
    }
} // namespace ntt
