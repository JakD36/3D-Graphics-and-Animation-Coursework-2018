//
// Created by Jack on 04/03/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DISABLESCISSORRECTCMD_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DISABLESCISSORRECTCMD_H

#include "../RenderCommand.h"

class DisableScissorRectCmd final : RenderCommand
{
public:
    DisableScissorRectCmd(unsigned long long sortKey) noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_DISABLESCISSORRECTCMD_H
