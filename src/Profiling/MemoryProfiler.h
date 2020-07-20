//
// Created by Jack Davidson on 20/07/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MEMORYPROFILER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MEMORYPROFILER_H

#include <cstdlib>
#include <cstdio>

#define MEM_PROFILE_SIZE 36000

void* operator new(size_t size);
void operator delete(void* memory, size_t size);

class MemoryProfiler {
private:
    inline static MemoryProfiler* m_instance = nullptr;

    size_t m_allocMemory[MEM_PROFILE_SIZE];

    size_t m_totalMemory;
    size_t m_totalFreedMemory;

    size_t m_frameIndex = 0;
public:
    MemoryProfiler();
    void Allocate(size_t size);
    void Free(size_t size);

    void NextFrame();
};

static MemoryProfiler s_memoryProfiler;

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MEMORYPROFILER_H
