//
// Created by Jack Davidson on 26/01/2021.
//

#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
    m_type = Type::BACK_BUFFER;
    m_resolution = {480,320};
}

RenderTarget::RenderTarget(Type type, glm::ivec2 size)
{
    m_type = type;
    m_resolution = size;

    if(type == Type::CUSTOM)
    {
        glGenFramebuffers(1, &m_framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

        glGenTextures(1, &m_colourAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colourAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear sample when texture is minified
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear sample when texture is magnified
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourAttachment, 0);

        glGenRenderbuffers(1, &m_depthAttachment);
        glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);

        ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,"Framebuffer failed to be created.");

        glBindFramebuffer(GL_FRAMEBUFFER,0);
    }
}

void RenderTarget::Bind() const
{
    switch (m_type)
    {
        case Type::BACK_BUFFER:
            glBindFramebuffer(GL_FRAMEBUFFER,0);
            break;
        case Type::CUSTOM:
            glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer);
            break;
    }
}