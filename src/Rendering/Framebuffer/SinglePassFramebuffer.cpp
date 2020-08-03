//
// Created by Jack Davidson on 17/06/2020.
//

#include "SinglePassFramebuffer.h"

SinglePassFramebuffer::SinglePassFramebuffer() noexcept : m_framebuffer(0) {};
SinglePassFramebuffer::~SinglePassFramebuffer() noexcept {};

void SinglePassFramebuffer::RenderTo() const  noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer); // Rendering to framebuffer 1
}
void SinglePassFramebuffer::PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const  noexcept { }
