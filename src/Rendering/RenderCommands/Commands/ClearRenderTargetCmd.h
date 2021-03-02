//
// Created by Jack on 02/03/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_CLEARRENDERTARGETCMD_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_CLEARRENDERTARGETCMD_H

#include "../RenderCommand.h"

class ClearRenderTargetCmd final: public RenderCommand
{
public:
    bool m_clearDepth;
    bool m_clearColour;
    glm::vec4 m_colour;
    float m_depth;

    ClearRenderTargetCmd(bool clearDepth, bool clearColour, glm::vec4 colour, float depth) noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_CLEARRENDERTARGETCMD_H
