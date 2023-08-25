#pragma once


namespace ntt
{
    class IndexBuffer
    {
        public:
            IndexBuffer(unsigned int* indeces, unsigned int size);
            virtual ~IndexBuffer();

            virtual void Bind();
            virtual void UnBind();

            inline int GetCount() const { return count_; };
            virtual void Render(int count = 0);

        private:
            unsigned int id_;
            int count_;
    }; 
} // namespace ntt
