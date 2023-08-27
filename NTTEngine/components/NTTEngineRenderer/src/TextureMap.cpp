#include <sstream>
#include <imgui.h>
#include "NTTEngineUtils/NTTEngineUtils.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/TextureMap.hpp"
#include "NTTEngineRenderer/Texture.hpp"
#include "NTTEngineRenderer/SubTexture.hpp"
#include "NTTEngineRenderer/Renderer2D.hpp"
#include "Storage.hpp"


namespace ntt
{
    TextureMap::TextureMap(const char* name, std::shared_ptr<Texture2D> texture, 
                int widthNum, int heightNum, int tileSize)
        : name_(name), textureHeightNum_(heightNum), textureWidthNum_(widthNum)
    {
        storage_ = std::make_shared<Storage>(
            std::make_shared<RealFileSystem>("." + std::string(name) + "-texture-map.json")
        );

        mapWidthNum_ = 
            std::make_shared<ThreadValue<int>>(1, 1, 50, storage_, "mapWidthNum");
        mapHeightNum_ = 
            std::make_shared<ThreadValue<int>>(1, 1, 50, storage_, "mapHeightNum");

        for (int i=0; i<heightNum; i++)
        {
            for (int j=0; j<widthNum; j++)
            {
                auto subTexture = std::make_shared<SubTexture2D>(
                                texture, i, j, tileSize
                );
                
                subTextures_.push_back(subTexture);
            }
        }

        subTextsVectors_ = LoadSubTextureMap();
    }    

    std::vector<std::vector<int>> TextureMap::LoadSubTextureMap()
    {
        std::vector<std::vector<int>> result(mapHeightNum_->GetValue(), 
                                                std::vector<int>(mapWidthNum_->GetValue(), 0));
        std::vector<int> subTexturesArray;

        for (int i=0; i<mapHeightNum_->GetValue(); i++)
        {
            for (int j=0; j<mapWidthNum_->GetValue(); j++)
            {
                subTexturesArray.push_back(0);
            }
        }

        auto loadedData = storage_->GetValue<std::vector<int>>("subTextureMap", subTexturesArray);

        for (int i=0; i<mapHeightNum_->GetValue(); i++)
        {
            for (int j=0; j<mapWidthNum_->GetValue(); j++)
            {
                result[i][j] = loadedData[i * mapWidthNum_->GetValue() + j];
            }
        }

        return result;
    }

    static std::vector<int> Flatten(std::vector<std::vector<int>> mat)
    {
        std::vector<int> result;

        for (int i=0; i<mat.size(); i++)
        {
            for (int j=0; j<mat[0].size(); j++)
            {
                result.push_back(mat[i][j]);
            }
        }
        return result;
    }

    TextureMap::~TextureMap()
    {
        mapWidthNum_->Save();
        mapHeightNum_->Save();

        storage_->SetValue<std::vector<int>>("subTextureMap", Flatten(subTextsVectors_));

        storage_->Save();
    }

    void TextureMap::OnUpdate(ntt::Timestep ts)
    {
        int mapHeightNum = mapHeightNum_->GetValue();
        int mapWidthNum = mapWidthNum_->GetValue();

        for (int i=0; i<mapHeightNum; i++)
        {
            for (int j=0; j<mapWidthNum; j++)
            {
                int subTextureIndex = subTextsVectors_[i][j];
                auto subTexture = subTextureIndex < subTextures_.size() ? subTextures_[subTextureIndex]
                                        : subTextures_[0];
                Renderer2D::DrawQuad(
                    { j * 0.2, (mapWidthNum - i) * 0.2 },
                    { 0.2, 0.2 },
                    subTexture
                );
            }
        }
    }

    void TextureMap::OnImGuiRender(ntt::Timestep ts)
    {
        ImGui::Separator();

        ImGui::Text("Texture Map: ");
        ImGui::SameLine();
        ImGui::Text(name_);

        static int mapWidthNum = mapWidthNum_->GetValue();
        static int mapHeightNum = mapHeightNum_->GetValue();

        ImGui::InputInt("Width Num", &mapWidthNum, 
                        mapWidthNum_->GetMinValue(), mapWidthNum_->GetMaxValue());

        ImGui::InputInt("Height Num", &mapHeightNum, 
                        mapHeightNum_->GetMinValue(), mapHeightNum_->GetMaxValue());

        if (ImGui::Button("New map"))
        {
            subTextsVectors_ = std::vector<std::vector<int>>(mapHeightNum, 
                                                std::vector<int>(mapWidthNum, 0));
            *mapWidthNum_->GetPointer() = mapWidthNum;
            *mapHeightNum_->GetPointer() = mapHeightNum;
        }

        ImGui::Text("Map");

        for (int i=0; i<mapHeightNum_->GetValue(); i++)
        {
            for (int j=0; j<mapWidthNum_->GetValue(); j++)
            {
                static int selected = 0;
                std::ostringstream buttonName;
                buttonName << "(" << std::setw(2) << std::setfill('0') << std::to_string(i) 
                                        << ", " << std::to_string(j) << ") - "
                                        << std::setw(3) << std::setfill('0') 
                                        << std::to_string(subTextsVectors_[i][j]);
                if (ImGui::Button(buttonName.str().c_str()))
                {

                }
                if (ImGui::BeginPopupContextItem())
                {
                    static int chooseHeightIndex = 0;
                    static int chooseWidthIndex = 0;
                    std::string heightIndexStr = "Choose Height Index" + buttonName.str();
                    std::string widthIndexStr = "Choose Width Index" + buttonName.str();
                    ImGui::InputInt(heightIndexStr.c_str(), &chooseHeightIndex, 0, textureHeightNum_ - 1);
                    ImGui::InputInt(widthIndexStr.c_str(), &chooseWidthIndex, 0, textureWidthNum_ - 1);
                    if (ImGui::Button("Set"))
                    {
                        subTextsVectors_[i][j] = chooseWidthIndex * textureWidthNum_ + chooseHeightIndex;
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Set To All"))
                    {
                        auto value = chooseWidthIndex * textureWidthNum_ + chooseHeightIndex;
                        for (int i=0; i<subTextsVectors_.size(); i++)
                        {
                            for (int j=0; j<subTextsVectors_[i].size(); j++)
                            {
                                subTextsVectors_[i][j] = value;
                            }
                        }
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
                if (j != mapWidthNum_->GetValue() -1)
                {
                    ImGui::SameLine();
                }
            }
        }

        ImGui::Separator();
    }
} // namespace ntt
