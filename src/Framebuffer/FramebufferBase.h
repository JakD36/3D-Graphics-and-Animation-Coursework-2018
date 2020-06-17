//
// Created by Jack Davidson on 17/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FRAMEBUFFERBASE_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FRAMEBUFFERBASE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class FramebufferBase
{
protected:
    GLuint m_framebuffer;
public:
    FramebufferBase() noexcept;
    virtual ~FramebufferBase() noexcept;

    virtual void RenderTo() const noexcept = 0;
    virtual void PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const noexcept = 0;
    // TODO: Consider a post scene render call, so we specify internally where we are rendering and then render the scene as normal before calling the post render
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_FRAMEBUFFERBASE_H
