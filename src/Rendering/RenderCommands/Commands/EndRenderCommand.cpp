//
// Created by Jack Davidson on 24/12/2020.
//

#include "EndRenderCommand.h"

EndRenderCommand::EndRenderCommand() noexcept : RenderCommand(Type::END,UINT64_MAX) {}