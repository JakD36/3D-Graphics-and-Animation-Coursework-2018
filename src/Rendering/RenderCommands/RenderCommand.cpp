//
// Created by Jack Davidson on 23/12/2020.
//

#include "RenderCommand.h"

RenderCommand::RenderCommand(Type type, unsigned long sortKey) noexcept : m_type(type), m_sortKey(sortKey) {}

RenderCommand::Type RenderCommand::GetType() const noexcept
{
    return m_type;
}

unsigned long RenderCommand::GetSortKey() const noexcept
{
    return m_sortKey;
}