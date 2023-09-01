#include "OpenGLPreInclude.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/FrameBuffer.hpp"
#include "NTTEngineLog/NTTEngineLog.hpp"


namespace ntt
{
    FrameBuffer::FrameBuffer(int width, int height)
        : FrameBuffer(width, height, GL_RGBA)
    {

    }

    void FrameBuffer::Invalid()
    {
        glCreateFramebuffers(1, &fboId_);
        Bind();

        glCreateTextures(GL_TEXTURE_2D, 1, &fboColorAttachmentId_);
        glBindTexture(GL_TEXTURE_2D, fboColorAttachmentId_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
        // glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboColorAttachmentId_, 0);

        // glCreateTextures(GL_TEXTURE_2D, 1, &fboDepthAttachmentId_);
        // glBindTexture(GL_TEXTURE_2D, fboDepthAttachmentId_);
        // glTexStorage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width_, height_);
        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fboDepthAttachmentId_, 0);
        // glBindTexture(GL_TEXTURE_2D, 0);

        // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboDepthAttachmentId_, 0);


        GLenum framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE) 
        {
            NTT_ENGINE_CRITICAL("Frame Buffer setup is wrong");
        }
        else 
        {
            NTT_ENGINE_INFO("FrameBuffer setup Successfully");
        }

        UnBind();
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteTextures(1, &fboColorAttachmentId_);
        // glDeleteTextures(1, &fboDepthAttachmentId_);
        glDeleteFramebuffers(1, &fboId_);
    }

    void FrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fboId_);
    }

    void FrameBuffer::UnBind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::SetSize(int width, int height)
    {
        width_ = width;
        height_ = height;
        Invalid();
    }
} // namespace ntt
