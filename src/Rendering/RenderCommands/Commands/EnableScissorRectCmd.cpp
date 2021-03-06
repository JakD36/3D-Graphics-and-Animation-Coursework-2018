//
// Created by Jack on 04/03/2021.
//

#include "EnableScissorRectCmd.h"

EnableScissorRectCmd::EnableScissorRectCmd(glm::vec4 rect) noexcept
    : RenderCommand(Type::ENABLE_SCISSOR_RECT, 1), m_rect(rect)
{}