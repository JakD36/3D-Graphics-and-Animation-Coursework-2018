//
// Created by Jack Davidson on 15/01/2021.
//

#include "BeginWithRtRenderCommand.h"

BeginWithRtRenderCommand::BeginWithRtRenderCommand(RenderTarget rt):
    RenderCommand(Type::BEGIN_WITH_RT,0), m_rt(rt)
    {}