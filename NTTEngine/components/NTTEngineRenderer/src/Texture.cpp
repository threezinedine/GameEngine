#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/Shader.hpp"
#include "NTTEngineRenderer/Texture.hpp"


namespace ntt
{
    bool Texture2D::EqualTo(const Texture& other)
    {
        return id_ == static_cast<const Texture2D&>(other).id_;
    }

    bool Texture2D::EqualTo(const std::shared_ptr<Texture>& other)
    {
        return id_ == std::dynamic_pointer_cast<Texture2D>(other)->id_;
    }
} // namespace ntt
