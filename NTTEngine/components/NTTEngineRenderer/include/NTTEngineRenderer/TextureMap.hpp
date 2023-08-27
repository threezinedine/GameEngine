#pragma once
#include <vector>
#include <memory>
#include "NTTEngineThreadSystem/NTTEngineThreadSystem.hpp"


namespace ntt
{
    class Texture2D;
    class SubTexture2D;
    class Timestep;
    class Storage;

    class TextureMap
    {
        public:
            TextureMap(const char* name, std::shared_ptr<Texture2D> texture, 
                        int widthNum, int heightNum, int tileSize);
            ~TextureMap();

            void OnUpdate(ntt::Timestep ts);

            void OnImGuiRender(ntt::Timestep ts);

        private:
            const char* name_;
            std::shared_ptr<Texture2D> texture_;
            std::vector<std::shared_ptr<SubTexture2D>> subTextures_;

            std::vector<std::vector<int>> subTextsVectors_;

            std::shared_ptr<Storage> storage_;
            std::shared_ptr<ThreadValue<int>> mapWidthNum_;
            std::shared_ptr<ThreadValue<int>> mapHeightNum_;

            int textureWidthNum_;
            int textureHeightNum_;

            std::vector<std::vector<int>> LoadSubTextureMap();
            void SaveSubTextureMap();
    };
} // namespace ntt
