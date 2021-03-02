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
        CLEAR,
        BLIT,

        CLEAR_RENDER_TARGET,
        COPY_TEXTURE,

        DRAW_MESH,
        DRAW_MESH_INSTANCED,
        DRAW_MESH_INSTANCED_INDIRECT,
        DRAW_RENDERER, // Unity Specific, May not need

        ENABLE_SCISSOR_RECT,
        DISABLE_SCISSOR_RECT,
        GENERATE_RT_MIPS,

        GET_TMP_RT,
        GET_TMP_RT_ARRAY,

        SET_GLOBAL_BUFFER,
        SET_GLOBAL_FLOAT,
        SET_GLOBAL_FLOAT_ARRAY,

        SET_GLOBAL_INT,

        SET_GLOBAL_MATRIX,
        SET_GLOBAL_MATRIX_ARRAY,

        SET_GLOBAL_TEXTURE,

        SET_GLOBAL_VECTOR,
        SET_GLOBAL_VECTOR_ARRAY,

        SET_PROJECTION_MATRIX,
        SET_VIEW_MATRIX,
        SET_VIEW_PROJECTION_MATRICES,
        SET_RENDER_TARGET,
        SET_VIEWPORT,

        DRAW_RENDERERS, // Compatibility command with old rendering process
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
