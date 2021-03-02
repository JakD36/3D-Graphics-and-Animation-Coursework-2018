//
// Created by Jack Davidson on 31/12/2020.
//

#include "BlitRenderCommand.h"

BlitRenderCommand::BlitRenderCommand(const RenderTarget &src, const RenderTarget& dest, unsigned long long sortKey) noexcept
        : RenderCommand(Type::BLIT, sortKey), m_src(src), m_dest(dest)
{
}