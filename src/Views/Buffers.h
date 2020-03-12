//
// Created by Jack Davidson on 10/03/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BUFFERS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BUFFERS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Shaders/ShaderManager.h"

class FramebufferBase
{
protected:
    GLuint m_framebuffer;
public:
    FramebufferBase();
    virtual ~FramebufferBase();

    virtual void RenderTo() const = 0;
    virtual void PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const = 0;
    // TODO: Consider a post scene render call, so we specify internally where we are rendering and then render the scene as normal before calling the post render
};

class SinglePassFramebuffer : public FramebufferBase
{
protected:
    GLuint m_framebuffer;
public:
    SinglePassFramebuffer();
    virtual ~SinglePassFramebuffer();

    virtual void RenderTo() const;
    virtual void PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const;
};

class TwoPassFramebuffer : public FramebufferBase
{
private:
    GLuint m_framebuffer;
    GLuint m_framebufferTexture;
    GLuint m_depthbuffer;

    GLuint m_displayVao;
    GLuint m_displayBuffer;

    GLuint m_framebufferProgram;

    const glm::vec2 m_displayCoords[12] = { // Interleaved coordinates for displaying to a Quad
            glm::vec2(-1.0f, 1.0f), // v
            glm::vec2(0.0f, 1.0f), // uv
            glm::vec2(-1.0f,-1.0f), // v
            glm::vec2(0.0f, 0.0f), // uv
            glm::vec2( 1.0f,-1.0f), // v
            glm::vec2(1.0f, 0.0f), // uv
            glm::vec2(-1.0f, 1.0f), // v
            glm::vec2(0.0f, 1.0f), // uv
            glm::vec2( 1.0f,-1.0f), // v
            glm::vec2(1.0f, 0.0f), // uv
            glm::vec2( 1.0f, 1.0f),// v
            glm::vec2(1.0f, 1.0f) // uv
    };

    void InitFramebuffer(int frameWidth, int frameHeight);
    void InitDepthbuffer(int frameWidth, int frameHeight);
public:
    TwoPassFramebuffer();
    TwoPassFramebuffer(int frameWidth, int frameHeight);
    ~TwoPassFramebuffer();

    virtual void RenderTo() const;
    virtual void PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const;
    // TODO: Consider a post scene render call, so we specify internally where we are rendering and then render the scene as normal before calling the post render
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BUFFERS_H