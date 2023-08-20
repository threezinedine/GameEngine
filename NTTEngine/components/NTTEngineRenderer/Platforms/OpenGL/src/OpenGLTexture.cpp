#include <opencv2/opencv.hpp>
#include "NTTEngineLog/NTTEngineLog.hpp"
#include "GL_ASSERTION.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"

namespace ntt
{
    Texture2D::Texture2D(std::string file)
    {
        cv::Mat image = cv::imread(file);

        GLenum internalFormat = 0, dataFormat = GL_RGB;

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

        cv::resize(image, image, cv::Size(300, 300));
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

        GL_CALL(glGenTextures(1, &id_));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, image.cols, image.rows, 
                        0, dataFormat, GL_UNSIGNED_BYTE, image.data));
    }  

    Texture2D::~Texture2D()
    {
        NTT_ENGINE_DEBUG("Start Delete Texture");
        GL_CALL(glDeleteTextures(1, &id_));
        NTT_ENGINE_DEBUG("Finish Delete Texture");
    }

    void Texture2D::Bind(uint32_t slot)
    {
        // glBindTextureUnit(slot, id_);
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
    }
} // namespace ntt
