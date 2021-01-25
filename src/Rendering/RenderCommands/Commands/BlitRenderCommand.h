//
// Created by Jack Davidson on 31/12/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BLITRENDERCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BLITRENDERCOMMAND_H

#include "../RenderCommand.h"

class BlitRenderCommand final: public RenderCommand
{
public:
    RenderTarget m_src; // TODO: Change these to some generic
    RenderTarget m_dest;
    BlitRenderCommand(const RenderTarget &src, const RenderTarget& dest, unsigned long sortKey) noexcept;
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_BLITRENDERCOMMAND_H
