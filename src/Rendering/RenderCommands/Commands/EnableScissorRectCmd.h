//
// Created by Jack on 04/03/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_ENABLESCISSORRECTCMD_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_ENABLESCISSORRECTCMD_H

#include "../RenderCommand.h"

class EnableScissorRectCmd : public RenderCommand
{
public:
    glm::vec4 m_rect;

    EnableScissorRectCmd(glm::vec4 rect) noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_ENABLESCISSORRECTCMD_H
