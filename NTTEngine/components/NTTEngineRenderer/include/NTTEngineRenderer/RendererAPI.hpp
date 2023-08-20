#pragma once
#include <memory>
#include "VertexArray.hpp"
#include "NTTEngineCore/NTTEngineCore.hpp"
#include "Shader.hpp"
#include "ICamera.hpp"


namespace ntt
{
    class RendererAPI
    {
        public:
            virtual ~RendererAPI();

            static void Init();
            static void Begin(std::shared_ptr<ICamera>& camera, Timestep ts);
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

            inline void SetCamera(std::shared_ptr<ICamera>& camera) { camera_ = camera; }

        private:
            std::shared_ptr<ICamera> camera_;
            static RendererAPI* instance_;
    };    
} // namespace ntt
