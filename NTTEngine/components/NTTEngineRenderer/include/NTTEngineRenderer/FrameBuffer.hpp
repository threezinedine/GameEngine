#pragma once


namespace ntt
{
    class FrameBuffer
    {
        public: 
            FrameBuffer(int width, int height);
            FrameBuffer(int width, int height, int format);
            ~FrameBuffer();

            void Invalid();

            void Bind();
            void UnBind();

            inline const unsigned int GetColorTextureId() const { return fboColorAttachmentId_; }

            void SetSize(int width, int height);

        private:
            int width_;
            int height_;
            int format_;

            unsigned int fboId_;
            unsigned int fboColorAttachmentId_;
            unsigned int fboDepthAttachmentId_;
    };    
} // namespace ntt
