//
// Created by Jack Davidson on 20/07/2020.
//

#include "MemoryProfiler.h"

void* operator new(size_t size)
{
    s_memoryProfiler.Allocate(size);
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    s_memoryProfiler.Free(size);
    return free(memory);
}

MemoryProfiler::MemoryProfiler(){}

void MemoryProfiler::Allocate(size_t size) {
    m_totalMemory += size;
    m_allocMemory[m_frameIndex] += size;
}

void MemoryProfiler::Free(size_t size) {
    m_totalFreedMemory += size;
    m_allocMemory[m_frameIndex] -= size;
}

void MemoryProfiler::NextFrame() {
    size_t newIndex = (m_frameIndex + 1) % MEM_PROFILE_SIZE;
    m_allocMemory[newIndex] = m_allocMemory[m_frameIndex];
    m_frameIndex = newIndex;
}