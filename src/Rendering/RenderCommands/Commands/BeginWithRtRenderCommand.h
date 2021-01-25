//
// Created by Jack Davidson on 15/01/2021.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BEGINWITHRTRENDERCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BEGINWITHRTRENDERCOMMAND_H

#include "../RenderCommand.h"

class BeginWithRtRenderCommand : public RenderCommand
{
public:
    RenderTarget m_rt;
    BeginWithRtRenderCommand(RenderTarget rt);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BEGINWITHRTRENDERCOMMAND_H
