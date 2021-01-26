//
// Created by Jack Davidson on 23/12/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMAND_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMAND_H


#include "../../Utils/DebugUtils.h"

class RenderTarget
{
public:
    enum class Type
    {
        BACK_BUFFER,
        CUSTOM
    };

    Type m_type;

    GLuint m_framebuffer;
    GLuint m_colourAttachment;
    GLuint m_depthAttachment;

    glm::ivec2 m_resolution;

    RenderTarget()
    {
        m_type = Type::BACK_BUFFER;
        m_resolution = {480,320};
    }

    RenderTarget(Type type, glm::ivec2 size)
    {
        m_type = type;
        m_resolution = size;

        if(type == Type::CUSTOM)
        {
            glGenFramebuffers(1, &m_framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

            glGenTextures(1, &m_colourAttachment);
            glBindTexture(GL_TEXTURE_2D, m_colourAttachment);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear sample when texture is minified
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear sample when texture is magnified
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colourAttachment, 0);

            glGenRenderbuffers(1, &m_depthAttachment);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);

            assertm(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,"Framebuffer failed to be created.");

            glBindFramebuffer(GL_FRAMEBUFFER,0);
        }
    }

    void Bind() const
    {
        switch (m_type)
        {
            case Type::BACK_BUFFER:
                glBindFramebuffer(GL_FRAMEBUFFER,0);
                break;
            case Type::CUSTOM:
                glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer); // Rendering to framebuffer 1
                break;
        }

    }
};

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

enum class SortKey_Order : unsigned long
{
    UNUSED = 1lu << 62lu,
    LAYERS = 1lu << 55lu,
    SHADER_SYSTEM_DEFERRED = 1lu << 52lu,
    USER = 1lu << 20lu,
    INSTANCE = 1lu << 19lu,
    DEPTH = 1lu << 3lu,
    SHADER_SYSTEM_IMMEDIATE = 1lu << 0
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
        SET_GLOBAL_MATRIX,
        SET_GLOBAL_TEXTURE,
        SET_GLOBAL_VECTOR,
        SET_PROJECTION_MATRIX,
        SET_RENDER_TARGET,
        SET_VIEWPORT
    };

    Type GetType() const noexcept;
    unsigned long GetSortKey() const noexcept;

    virtual ~RenderCommand() noexcept {}
protected:
    RenderCommand(Type type, unsigned long m_sortKey) noexcept;
private:
    Type m_type;
    unsigned long m_sortKey; // 64 bit key for sorting all the commands
};


class DrawMeshCommand : public RenderCommand
{
public:
    DrawMeshCommand() : RenderCommand(Type::DRAW_MESH,1){}
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERCOMMAND_H
