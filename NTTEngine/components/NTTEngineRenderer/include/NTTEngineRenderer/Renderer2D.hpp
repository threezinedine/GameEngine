#pragma once
#include <glm/glm.hpp>
#include <memory>


namespace ntt
{
    class Camera;
    class VertexArray;
    class RendererCommand;
    class Texture;
    class Shader;

    class Renderer2D
    {
        public:
            static void Init();
            static void Release();

            static void BeginScence(std::shared_ptr<Camera> camera, Timestep ts);
            static void End();

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

            void InitIn();
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor);

            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const glm::vec3& color);
            void DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor);
    };
} // namespace ntt
