#pragma once
#include <glm/glm.hpp>
#include <memory>

#define MAX_BATCH               10000
#define MAX_VERTEX_BUFFER       MAX_BATCH * 4
#define MAX_INDEX_BUFFER        MAX_BATCH * 6


namespace ntt
{
    class Camera;
    class VertexArray;
    class RendererCommand;
    class Texture;
    class Shader;

    struct VertexData
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 coord;
    };

    class Renderer2D
    {
        public:
            static void Init();
            static void Release();

            static void BeginScene(std::shared_ptr<Camera> camera, Timestep ts);
            static void EndScene();

            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

            static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotate, const glm::vec3& color);
            static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotate, const glm::vec3& color);
            static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });
            static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

        private:
            static Renderer2D* instance_;
            static Renderer2D* GetInstance() { return instance_; }

            std::shared_ptr<VertexArray> vao_;
            std::shared_ptr<Shader> shader_;
            std::shared_ptr<Texture> whiteTexture_;

            VertexData* vertexDatas_;
            VertexData* ptr_;

            void InitIn();
            void BeginSceneIn();

            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor);

            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const glm::vec3& color);
            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor);

            void EndSceneIn();
            void ReleaseIn();
    };
} // namespace ntt
