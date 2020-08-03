//
// Created by Jack Davidson on 10/03/2020.
//

#include <DearImgui/imgui.h>
#include "TwoPassFramebuffer.h"
#include "../Shaders/ShaderManager.h"

using namespace std;

void TwoPassFramebuffer::RenderTo() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer); // Rendering to framebuffer 1
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_framebufferTexture,0);
}
void TwoPassFramebuffer::PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    glScissor(viewportX, viewportY, viewportWidth, viewportHeight);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // not needed as we are just displaying a single quad

    glUseProgram(m_framebufferProgram);
    glBindVertexArray(m_displayVao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

TwoPassFramebuffer::TwoPassFramebuffer(int frameWidth, int frameHeight) noexcept
{
    InitFramebuffer(frameWidth, frameHeight);
    InitDepthbuffer(frameWidth, frameHeight);

    { // Stored Quad verts + UVs for framebuffer
        glGenBuffers(1, &m_displayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_displayBuffer);
        glBufferData(GL_ARRAY_BUFFER,
                     12 * sizeof(glm::vec2),
                     &m_displayCoords[0],
                     GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_displayVao);
        glBindVertexArray(m_displayVao);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), NULL);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), (GLvoid *) (sizeof(glm::vec2)));
        glEnableVertexAttribArray(1);
    }

    ShaderManager* shaderManager = ShaderManager::GetInstance();
    m_framebufferProgram = shaderManager->RequestProgram("Shaders/vs_display.glsl","Shaders/fs_display.glsl");
}

TwoPassFramebuffer::~TwoPassFramebuffer() noexcept
{
    glDeleteBuffers(1,&m_framebuffer);
    glDeleteTextures(1,&m_framebufferTexture);
    glDeleteBuffers(1,&m_depthbuffer);

    glDeleteBuffers(1,&m_displayBuffer);
    glDeleteVertexArrays(1,&m_displayVao);
}

void TwoPassFramebuffer::InitFramebuffer(int frameWidth, int frameHeight) noexcept
{
    // Setup the framebuffer using the following code taken from the the lecture notes and code
    /*
        Frame buffer 0 is is our screen,
        Frame buffer 1 is where we render to do perform our post processing effects
    */
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glGenTextures(1, &m_framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frameWidth, frameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear sample when texture is minified
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear sample when texture is magnified
}

void TwoPassFramebuffer::InitDepthbuffer(int frameWidth, int frameHeight) noexcept
{   // Depth buffer texture - Need to attach depth too otherwise depth testing will not be performed.
    glGenRenderbuffers(1, &m_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbuffer);
}

