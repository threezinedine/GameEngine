#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>


namespace ntt
{
    class Texture2D;

    class SubTexture2D
    {
        public:
            SubTexture2D(std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
            SubTexture2D(std::shared_ptr<Texture2D>& texture, int xPos, int yPos, int tileSize);
            ~SubTexture2D();

            inline const std::vector<glm::vec2>& GetTextureCoords() const { return texCoords_; }
            inline std::shared_ptr<Texture2D> GetTexture() { return texture_; }

        private:
            std::vector<glm::vec2> texCoords_;
            std::shared_ptr<Texture2D> texture_;
    }; 
} // namespace ntt
