//
// Created by Jack Davidson on 23/12/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMAND_H

/* From Stingray blog https://bitsquid.blogspot.com/2017/02/stingray-renderer-walkthrough-4-sorting.html
MSB [ 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 ] LSB
^ ^       ^  ^                                   ^^                 ^
| |       |  |                                   ||                 |- 3 bits - Shader System (Pass Immediate)
| |       |  |                                   ||- 16 bits - Depth
| |       |  |                                   |- 1 bit - Instance bit
| |       |  |- 32 bits - User defined
| |       |- 3 bits - Shader System (Pass Deferred)
| - 7 bits - Layer System
|- 2 bits - Unused
 */

enum class SortKey_Order : unsigned long long
{
    UNUSED = 1llu << 62llu,
    LAYERS = 1llu << 55llu,
    SHADER_SYSTEM_DEFERRED = 1llu << 52llu,
    USER = 1llu << 20llu,
    INSTANCE = 1llu << 19llu,
    DEPTH = 1llu << 3llu,
    SHADER_SYSTEM_IMMEDIATE = 1llu << 0
};

class RenderCommand
{
public:
    enum class Type
    {
        BEGIN,
        BEGIN_WITH_RT,
        END,
        BLIT,
        CLEAR_RENDER_TARGET,
        COPY_TEXTURE,
        DRAW_MESH,
        DRAW_RENDERERS,
        SET_GLOBAL_MATRIX,
        SET_GLOBAL_TEXTURE,
        SET_GLOBAL_VECTOR,
        SET_PROJECTION_MATRIX,
        SET_RENDER_TARGET,
        SET_VIEWPORT
    };

    Type GetType() const noexcept;
    unsigned long long GetSortKey() const noexcept;

    virtual ~RenderCommand() noexcept {}
protected:
    RenderCommand(Type type, unsigned long long m_sortKey) noexcept;
private:
    Type m_type;
    unsigned long m_sortKey; // 64 bit key for sorting all the commands
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMAND_H
