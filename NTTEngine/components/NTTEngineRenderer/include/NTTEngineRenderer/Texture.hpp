#pragma once
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <opencv2/opencv.hpp>


namespace ntt
{
    class Texture
    {
        public:
            virtual const unsigned int GetWidth() const = 0;
            virtual const unsigned int GetHeight() const = 0;
            virtual void SetData(cv::Mat image) = 0;

            virtual void Bind(uint32_t slot = 0) = 0;
            virtual void UnBind() = 0;

            virtual bool EqualTo(const Texture& other) = 0;
            virtual bool EqualTo(const std::shared_ptr<Texture>& other) = 0;
    }; 

    class Texture2D: public Texture
    {
        public:
            Texture2D(int width, int height);
            Texture2D(std::string path, int width = 300, int height = 300);
            Texture2D(std::string path, int widthNum, int heightNum, int tileSize);
            ~Texture2D();

            inline const unsigned int GetWidth() const { return width_; }
            inline const unsigned int GetHeight() const { return height_; }

            void Bind(uint32_t slot = 0) override;
            void UnBind() override;
            void SetData(cv::Mat image) override;

            bool EqualTo(const Texture& other) override;
            bool EqualTo(const std::shared_ptr<Texture>& other) override;

        private:
            unsigned int width_;
            unsigned int height_;
            unsigned int id_;
            GLenum internalFormat_;
            GLenum dataFormat_;

            // inline const unsigned int GetId() const { return id_; }
    };
} // namespace ntt
