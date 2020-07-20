//
// Created by Jack Davidson on 20/07/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MEMORYPROFILER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MEMORYPROFILER_H

#include <cstdlib>
#include <cstdio>

#define MEM_PROFILE_SIZE 1800

class MemoryProfiler {
private:
    const float k_graphSize = 150.f;

    MemoryProfiler();
    inline static MemoryProfiler *m_instance = nullptr;
    float m_memArray[MEM_PROFILE_SIZE];
    float m_drawArray[MEM_PROFILE_SIZE];

    size_t m_totalMemory;
    size_t m_totalFreedMemory;

    size_t m_frameIndex = 0;
public:
    enum class SizeType
    {
        BYTES,
        KILOBYTES,
        MEGABYTES
    };

    static MemoryProfiler* GetInstance();
    void Allocate(size_t size);
    void Free(size_t size);

    void NextFrame();

    SizeType m_sizeType;

    void Draw();
    void Clear();
    void* operator new(size_t size);

    size_t m_newCalls;
    size_t m_deleteCalls;
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MEMORYPROFILER_H
