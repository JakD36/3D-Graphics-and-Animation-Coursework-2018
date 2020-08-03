//
// Created by Jack Davidson on 10/05/2020.
//


#include "RenderTask.h"

RenderTask::RenderTask(std::string filepath)
{
    m_manager = ResourceManager<RenderTaskResource>::GetInstance();
    m_key = m_manager->Request(filepath);
}

RenderTask::RenderTask(const RenderTask &cp)
{
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
}

RenderTask::~RenderTask()
{
    m_manager->Dispose(m_key);
}

size_t RenderTask::size()
{
    return m_manager->m_data[m_key].m_passes.size();
}

RenderPass & RenderTask::operator[](const size_t &index) noexcept
{
    return m_manager->m_data[m_key].m_passes[index];
}

std::string RenderTask::GetName()
{
    return m_manager->m_data[m_key].m_name;
}