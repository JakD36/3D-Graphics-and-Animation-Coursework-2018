//
// Created by Jack on 04/03/2021.
//

#include "DisableScissorRectCmd.h"

DisableScissorRectCmd::DisableScissorRectCmd(unsigned long long sortKey) noexcept
    : RenderCommand(Type::DISABLE_SCISSOR_RECT, sortKey)
{}