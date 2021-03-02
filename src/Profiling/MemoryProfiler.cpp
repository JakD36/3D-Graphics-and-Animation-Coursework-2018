//
// Created by Jack Davidson on 20/07/2020.
//

#include <imgui.h>
#include "MemoryProfiler.h"
#include <algorithm>

using namespace std;

void* operator new(size_t size)
{
    MemoryProfiler::GetInstance()->Allocate(size);
    ++MemoryProfiler::GetInstance()->m_newCalls;
    return malloc(size);
}

void* operator new[](size_t size)
{
    MemoryProfiler::GetInstance()->Allocate(size);
    ++MemoryProfiler::GetInstance()->m_newCalls;
    return malloc(size);
}

void operator delete(void* memory)
{
    ++MemoryProfiler::GetInstance()->m_deleteCalls;
    free(memory);
}

void operator delete[](void* memory)
{
    ++MemoryProfiler::GetInstance()->m_deleteCalls;
    free(memory);
}

void operator delete(void* memory, size_t size)
{
    MemoryProfiler::GetInstance()->Free(size);

    ++MemoryProfiler::GetInstance()->m_deleteCalls;
    free(memory);
}

void operator delete[](void* memory, size_t size)
{
    MemoryProfiler::GetInstance()->Free(size);

    ++MemoryProfiler::GetInstance()->m_deleteCalls;
    free(memory);
}

MemoryProfiler * MemoryProfiler::GetInstance() {
    if(m_instance == nullptr)
        m_instance = new MemoryProfiler();
    return m_instance;
}

MemoryProfiler::MemoryProfiler(){}

void MemoryProfiler::Allocate(size_t size) {

    m_totalMemory += size;
    m_memArray[m_frameIndex] += size;
}

void MemoryProfiler::Free(size_t size) {
    m_totalFreedMemory += size;
    m_memArray[m_frameIndex] -= size;
}

void MemoryProfiler::NextFrame() {
    size_t newIndex = (m_frameIndex + 1) % MEM_PROFILE_SIZE;
    m_memArray[newIndex] = m_memArray[m_frameIndex];
    m_frameIndex = newIndex;
}

void* MemoryProfiler::operator new(size_t size)
{
    return malloc(size);
}

void MemoryProfiler::Draw() {
    float multiplier;
    float maxVal = FLT_MIN;
    switch(m_sizeType)
    {
        case SizeType::BYTES:
            multiplier = 1.f;
            break;
        case SizeType::KILOBYTES:
            multiplier = 1.f / 1024.f;
            break;
        case SizeType::MEGABYTES:
            multiplier = 1.f / 1024.f / 1024.f;
            break;
    }

    size_t drawIndex = MEM_PROFILE_SIZE - 1;
    for(int i = m_frameIndex; i >= 0; --i)
    {
        float val = m_memArray[i] * multiplier;
        if(val > maxVal)
            maxVal = val;
        m_drawArray[drawIndex] = val;
        drawIndex--;
    }
    for(int i = MEM_PROFILE_SIZE - 1; i > m_frameIndex; --i)
    {
        float val = m_memArray[i] * multiplier;
        if(val > maxVal)
            maxVal = val;
        m_drawArray[drawIndex] = val;
        drawIndex--;
    }
    float scale = 1.05f * maxVal;
    ImGui::Text("New = %zu",m_newCalls);
    ImGui::Text("Delete = %zu",m_deleteCalls);
    ImGui::PlotLines("Memory", m_drawArray, MEM_PROFILE_SIZE, 0, 0, 0.0f, scale, ImVec2(0,150));
}

void MemoryProfiler::Clear() {
    for_each(begin(m_memArray),end(m_memArray),[](auto &x){ x = 0;});
}