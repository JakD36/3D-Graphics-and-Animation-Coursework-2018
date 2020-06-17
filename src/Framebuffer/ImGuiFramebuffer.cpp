//
// Created by Jack Davidson on 17/06/2020.
//

#include <vector>
#include "ImGuiFramebuffer.h"

#include "../Include/DearImgui/imgui.h"
#include "../Include/DearImgui/imgui_impl_opengl3.h"
#include "../Include/DearImgui/imgui_impl_glfw.h"



ImGuiFramebuffer::ImGuiFramebuffer(int frameWidth, int frameHeight) noexcept : m_frameWidth(frameWidth), m_frameHeight(frameHeight){

    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glGenTextures(1, &m_framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear sample when texture is minified
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear sample when texture is magnified

    glGenRenderbuffers(1, &m_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbuffer);
};

ImGuiFramebuffer::~ImGuiFramebuffer() noexcept
{
    glDeleteBuffers(1,&m_framebuffer);
    glDeleteTextures(1,&m_framebufferTexture);
};

void ImGuiFramebuffer::RenderTo() const  noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer); // Rendering to framebuffer 1
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_framebufferTexture,0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void ImGuiFramebuffer::PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const  noexcept
{
    ImGui::Begin("Viewport",NULL);
    ImGui::Image((void*)m_framebufferTexture, ImVec2(m_frameWidth * 0.25f, m_frameHeight * 0.25f), ImVec2(0,1), ImVec2(1,0), ImVec4(1.0f,1.0f,1.0f,1.0f), ImVec4(1.0f,1.0f,1.0f,0.5f));
    ImGui::End();

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
