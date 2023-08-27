#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/SubTexture.hpp"
#include "NTTEngineRenderer/Texture.hpp"


namespace ntt
{
    SubTexture2D::SubTexture2D(std::shared_ptr<Texture2D>& texture, 
            const glm::vec2& min, const glm::vec2& max)
        : texture_(texture)
    {
        texCoords_.push_back({ min.x, min.y });
        texCoords_.push_back({ max.x, min.y });
        texCoords_.push_back({ max.x, max.y });
        texCoords_.push_back({ min.x, max.y });
    } 

    SubTexture2D::SubTexture2D(std::shared_ptr<Texture2D>& texture, int xPos, int yPos, int tileSize)
        : texture_(texture)
    {
        texCoords_.push_back({ 
                    (float)xPos     * tileSize / texture->GetWidth(), 
                    (float)yPos     * tileSize / texture->GetHeight()
        });
        texCoords_.push_back({ 
                    (float)(xPos+1) * tileSize / texture->GetWidth(), 
                    (float)yPos     * tileSize / texture->GetHeight()
        });
        texCoords_.push_back({ 
                    (float)(xPos+1) * tileSize / texture->GetWidth(), 
                    (float)(yPos+1) * tileSize / texture->GetHeight()
        });
        texCoords_.push_back({ 
                    (float)xPos     * tileSize / texture->GetWidth(), 
                    (float)(yPos+1) * tileSize / texture->GetHeight()}
        );
    }

    SubTexture2D::~SubTexture2D()
    {

    }
} // namespace ntt
