//
// Created by Jack Davidson on 26/01/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTARGET_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTARGET_H


#include "../Utils/DebugUtils.h"

class RenderTarget
{
public:
    enum class Type
    {
        BACK_BUFFER,
        CUSTOM
    };

    Type m_type;

    GLuint m_framebuffer;
    GLuint m_colourAttachment;
    GLuint m_depthAttachment;

    glm::ivec2 m_resolution;

    RenderTarget();
    RenderTarget(Type type, glm::ivec2 size);
    void Bind() const;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERTARGET_H
