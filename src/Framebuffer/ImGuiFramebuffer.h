//
// Created by Jack Davidson on 17/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_IMGUIFRAMEBUFFER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_IMGUIFRAMEBUFFER_H

#include "FramebufferBase.h"



class ImGuiFramebuffer : public FramebufferBase{
protected:
    GLuint m_framebuffer;
    GLuint m_framebufferTexture;
    GLuint m_depthbuffer;

    int m_frameWidth, m_frameHeight;
public:
    ImGuiFramebuffer(int frameWidth, int frameHeight) noexcept;
    virtual ~ImGuiFramebuffer() noexcept;

    virtual void RenderTo() const noexcept;
    virtual void PostRender(int viewportX, int viewportY, int viewportWidth, int viewportHeight) const noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_IMGUIFRAMEBUFFER_H
