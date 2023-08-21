#pragma once
#include "glm/glm.hpp"
#include "Camera.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "RendererCommand.hpp"


namespace ntt
{
    class Renderer2D
    {
        public:
            static void Init();
            static void Release();

            static void BeginScence(std::shared_ptr<Camera> camera, Timestep ts);
            static void End();

            static void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec3& color);


        private:
            static Renderer2D* instance_;
            static Renderer2D* GetInstance() { return instance_; }

            std::shared_ptr<VertexArray> vao_;
            std::shared_ptr<Shader> shader_;

            void InitIn();
            void DrawQuadIn(glm::vec2 position, glm::vec2 size, glm::vec3& color);
    };
} // namespace ntt
