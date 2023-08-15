#pragma once
#include <string>
#include <NTTEngine/Renderer/Texture.hpp>


namespace ntt
{
    class OpenGLTexture2D: public Texture2D
    {
        public:
            OpenGLTexture2D(std::string path);
            ~OpenGLTexture2D();

            inline const unsigned int GetWidth() const { return width_; }
            inline const unsigned int GetHeight() const { return height_; }

            void Bind(uint32_t slot = 0) override;

        private:
            unsigned int width_;
            unsigned int height_;
            unsigned int id_;
    };
} // namespace ntt
