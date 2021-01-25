//
// Created by Jack Davidson on 24/12/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BEGINRENDERCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BEGINRENDERCOMMAND_H

#include "../RenderCommand.h"

class BeginRenderCommand final: public RenderCommand
{
public:
    glm::ivec2 m_position;
    glm::ivec2 m_resolution;
    glm::vec4 m_clearColour;
    BeginRenderCommand(const glm::ivec2 &position, const glm::ivec2 &resolution, const glm::vec4& clearColour) noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BEGINRENDERCOMMAND_H
