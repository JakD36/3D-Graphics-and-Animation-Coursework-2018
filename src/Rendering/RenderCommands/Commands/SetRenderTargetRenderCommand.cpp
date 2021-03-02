//
// Created by Jack Davidson on 31/12/2020.
//

#include "SetRenderTargetRenderCommand.h"

SetRenderTargetRenderCommand::SetRenderTargetRenderCommand(RenderTarget rt, unsigned long long sortKey)
: RenderCommand(Type::BLIT, sortKey), m_rt(rt)
{

}