//
// Created by Jack Davidson on 24/12/2020.
//

#include "BeginRenderCommand.h"

BeginRenderCommand::BeginRenderCommand(const glm::ivec2 &position, const glm::ivec2& resolution, const glm::vec4& clearColour) noexcept
        : RenderCommand(Type::BEGIN,0), m_position(position), m_resolution(resolution), m_clearColour(clearColour)
{
}