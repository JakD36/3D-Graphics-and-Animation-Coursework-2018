//
// Created by Jack Davidson on 17/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SINGLEPASSFRAMEBUFFER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SINGLEPASSFRAMEBUFFER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "FramebufferBase.h"

class SinglePassFramebuffer : public FramebufferBase
{
protected:
    GLuint m_framebuffer;
public:
    SinglePassFramebuffer() noexcept;
    virtual ~SinglePassFramebuffer() noexcept;

    virtual void RenderTo() const noexcept;
    virtual void PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SINGLEPASSFRAMEBUFFER_H
