#pragma once


namespace ntt
{
    class Texture
    {
        public:
            virtual const unsigned int GetWidth() const = 0;
            virtual const unsigned int GetHeight() const = 0;

            virtual void Bind(uint32_t slot = 0) = 0;
    }; 

    class Texture2D: public Texture
    {

    };
} // namespace ntt
