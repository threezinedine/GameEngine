#pragma once
#include <memory>
#include "VertexArray.hpp"


namespace ntt
{
    class RendererAPI
    {
        public:
            virtual ~RendererAPI();

            static void Begin();
            static void Submit(std::shared_ptr<VertexArray>& vertexArray);
            static void End();

            static RendererAPI* GetInstance();

            void DrawIndex(std::shared_ptr<VertexArray>& vertexArray); 
        protected:
            RendererAPI();

        private:
            static RendererAPI* instance_;
    };    
} // namespace ntt
