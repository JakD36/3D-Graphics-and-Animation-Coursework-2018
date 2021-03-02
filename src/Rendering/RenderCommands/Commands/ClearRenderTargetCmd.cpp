//
// Created by Jack on 02/03/2021.
//

#include "ClearRenderTargetCmd.h"

ClearRenderTargetCmd::ClearRenderTargetCmd(bool clearDepth, bool clearColour, glm::vec4 colour, float depth) noexcept
    : RenderCommand(Type::CLEAR_RENDER_TARGET, 0)/*todo Give Sort key*/,
    m_clearDepth(clearDepth), m_clearColour(clearColour), m_colour(colour), m_depth(depth)
{}