#pragma once
#include <vector>


namespace ntt
{
    class LayoutBuffer;

    class VertexBuffer
    {
        public:
            VertexBuffer(unsigned int size);
            VertexBuffer(float* data, unsigned int size);
            virtual ~VertexBuffer();

            virtual void Bind();
            virtual void UnBind();

            void RegisterBuffer(LayoutBuffer buffer);

            virtual void Setup();
            virtual void SetData(float* data, unsigned int count, unsigned int elementSize);
            inline bool IsDynamic() { return useDynamic_; }
            inline const unsigned int GetDynamicVertexesNum() const { return dynamicVertexsNum_; }

        protected:
            std::vector<LayoutBuffer> layouts_;

            unsigned int size_ = 0;
            unsigned int id_;

            bool useDynamic_ = false;
            unsigned int dynamicVertexsNum_ = 0; // use in dynamic only
    }; 
} // namespace ntt
