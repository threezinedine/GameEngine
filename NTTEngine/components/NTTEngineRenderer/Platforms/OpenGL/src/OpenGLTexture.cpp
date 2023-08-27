#include <opencv2/opencv.hpp>
#include "OpenGLPreInclude.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/Texture.hpp"

namespace ntt
{
    Texture2D::Texture2D(int width, int height)
        : width_(width), height_(height), internalFormat_(GL_RGB8),
            dataFormat_(GL_RGB)
    {
        PROFILE_SCOPE();
        GL_CALL(glGenTextures(1, &id_));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_, width, height, 
                        0, dataFormat_, GL_UNSIGNED_BYTE, nullptr);
    }

    Texture2D::Texture2D(std::string path, int widthNum, int heightNum, int tileSize)
        : Texture2D(path, widthNum * tileSize, heightNum * tileSize)
    {

    }

    Texture2D::Texture2D(std::string file, int width, int height)
        : width_(width), height_(height)
    {
        PROFILE_SCOPE();

        cv::Mat image = cv::imread(file, cv::IMREAD_UNCHANGED);

        cv::resize(image, image, cv::Size(width_, height_));
        cv::flip(image, image, 0);

        if (image.channels() == 4)
        {
            internalFormat_ = GL_RGBA8;
            dataFormat_ = GL_RGBA;
            cv::cvtColor(image, image, cv::COLOR_BGRA2RGBA);
        }
        else if (image.channels() == 3)
        {
            internalFormat_ = GL_RGB8;
            dataFormat_ = GL_RGB;
            cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        }

        GL_CALL(glGenTextures(1, &id_));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_, width_, height_, 
                        0, dataFormat_, GL_UNSIGNED_BYTE, nullptr);

        SetData(image);
    }  

    Texture2D::~Texture2D()
    {
        PROFILE_SCOPE();
        GL_CALL(glDeleteTextures(1, &id_));
    }

    void Texture2D::Bind(uint32_t slot)
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
    }

    void Texture2D::UnBind()
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Texture2D::SetData(cv::Mat image)
    {
        Bind();
        GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, 
                        dataFormat_, GL_UNSIGNED_BYTE, image.data));
    }
} // namespace ntt
