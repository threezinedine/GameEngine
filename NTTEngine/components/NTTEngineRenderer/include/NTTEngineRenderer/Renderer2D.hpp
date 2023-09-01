#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "RendererAPI.hpp"

namespace ntt
{
    class Camera;
    class VertexArray;
    class RendererCommand;
    class Texture2D;
    class Shader;
    class SubTexture2D;

    struct VertexData
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 coord;
        float texIndex;
    };

    struct DrawCallStatistic
    {
        int drawCallsCount;
        int quadDrawCallsCount;
        int vertexesCount;
        int indexesCount;

        int tempDrawCallsCount;
    };

    class Renderer2D
    {
        public:
            static void Init();
            static void Release();

            static void ResetStat();
            static void BeginScene(std::shared_ptr<Camera> camera, Timestep ts);
            static void EndScene();
            static void Clear() { RendererAPI::Clear(); }

            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, 
                                    const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, 
                                    const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, 
                                    const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, 
                                    const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, 
                                    const std::shared_ptr<SubTexture2D>& texture, float tilingFactor = 1.0f, 
                                    const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, 
                                    const std::shared_ptr<SubTexture2D>& texture, float tilingFactor = 1.0f, 
                                    const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

            static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, 
                                            float rotate, const glm::vec3& color);
            static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, 
                                            float rotate, const glm::vec3& color);
            static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, 
                                            float rotate, const std::shared_ptr<Texture2D>& texture, 
                                            float tilingFactor = 1.0f, const glm::vec4& tintColor = 
                                                { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, 
                                            float rotate, const std::shared_ptr<Texture2D>& texture, 
                                            float tilingFactor = 1.0f, const glm::vec4& tintColor = 
                                                { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, 
                                            float rotate, const std::shared_ptr<SubTexture2D>& texture, 
                                            float tilingFactor = 1.0f, const glm::vec4& tintColor = 
                                                { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, 
                                            float rotate, const std::shared_ptr<SubTexture2D>& texture, 
                                            float tilingFactor = 1.0f, const glm::vec4& tintColor = 
                                                { 1.0f, 1.0f, 1.0f, 1.0f });

            static void StatisticImGuiRender();

        private:
            static Renderer2D* instance_;
            static Renderer2D* GetInstance() { return instance_; }

            std::shared_ptr<VertexArray> vao_;
            std::shared_ptr<Shader> shader_;
            std::shared_ptr<Texture2D> whiteTexture_;

            VertexData* vertexDatas_;
            VertexData* ptr_;
            std::vector<std::shared_ptr<Texture2D>> textures_;
            DrawCallStatistic stats_;

            void InitIn();
            void ResetStatIn();
            void BeginSceneIn(bool resetTextures = true);

            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, 
                            const std::shared_ptr<Texture2D>& texture, float tilingFactor, 
                            const glm::vec4& tintColor);
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, 
                            const std::shared_ptr<SubTexture2D>& texture, float tilingFactor, 
                            const glm::vec4& tintColor);

            void DrawIn(const glm::vec3& position, const glm::vec3& color, float texIndex, 
                        const glm::mat4& transform = glm::mat4(1.0f), 
                        std::vector<glm::vec2> coords = 
                        { 
                            { 0.0f, 0.0f }, 
                            { 1.0f, 0.0f }, 
                            { 1.0f, 1.0f }, 
                            { 0.0f, 1.0f } 
                        });

            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, 
                                    float rotate, const glm::vec3& color);
            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, 
                                    float rotate, const std::shared_ptr<Texture2D>& texture, 
                                    float tilingFactor, const glm::vec4& tintColor);
            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, 
                                    float rotate, const std::shared_ptr<SubTexture2D>& texture, 
                                    float tilingFactor, const glm::vec4& tintColor);

            void EndSceneIn();
            void ReleaseIn();
    };
} // namespace ntt
