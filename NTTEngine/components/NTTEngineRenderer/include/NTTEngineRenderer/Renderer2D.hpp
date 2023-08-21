#pragma once
#include "glm/glm.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "RendererCommand.hpp"
#include "Texture.hpp"


namespace ntt
{
    class Renderer2D
    {
        public:
            static void Init();
            static void Release();

            static void BeginScence(std::shared_ptr<Camera> camera, Timestep ts);
            static void End();

            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
            static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);

        private:
            static Renderer2D* instance_;
            static Renderer2D* GetInstance() { return instance_; }

            std::shared_ptr<VertexArray> vao_;
            std::shared_ptr<Shader> shader_;
            std::shared_ptr<Texture> whiteTexture_;

            void InitIn();
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color);
            void DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
    };
} // namespace ntt
