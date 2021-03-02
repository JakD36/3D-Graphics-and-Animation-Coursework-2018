//
// Created by Jack Davidson on 31/12/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SETRENDERTARGETRENDERCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SETRENDERTARGETRENDERCOMMAND_H

#include "../RenderCommand.h"
#include "../../RenderTarget.h"

class SetRenderTargetRenderCommand : public RenderCommand
{
public:
    RenderTarget m_rt;
    SetRenderTargetRenderCommand(RenderTarget rt, unsigned long long sortKey);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_SETRENDERTARGETRENDERCOMMAND_H
