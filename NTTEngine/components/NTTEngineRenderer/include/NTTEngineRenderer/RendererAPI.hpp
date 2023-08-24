#pragma once
#include <memory>
#include <glm/glm.hpp>


namespace ntt
{
    class Camera;
    class Shader;
    class VertexArray;
    class Timestep;

    class RendererAPI
    {
        public:
            virtual ~RendererAPI();

            static void Init();
            static void Begin(std::shared_ptr<Camera>& camera, Timestep ts);
            static void Submit(std::shared_ptr<VertexArray>& vertexArray, 
                                std::shared_ptr<Shader>& shader, 
                                glm::mat4 transform = glm::mat4(1.0f));
            static void End();

            static RendererAPI* GetInstance();
            static void Release();

            void DrawIndex(std::shared_ptr<VertexArray>& vertexArray,
                            std::shared_ptr<Shader>& shader,
                            glm::mat4 transform);

        protected:
            RendererAPI();

            inline void SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

        private:
            std::shared_ptr<Camera> camera_;
            static RendererAPI* instance_;
    };    
} // namespace ntt
