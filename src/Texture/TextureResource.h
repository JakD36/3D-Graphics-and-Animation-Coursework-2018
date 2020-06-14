//
// Created by Jack Davidson on 14/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_TEXTURERESOURCE_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_TEXTURERESOURCE_H


#include "../Resource.h"
#include <string>
#include <GL/glew.h>

class TextureResource : public Resource {
public :
    TextureResource(std::string texturePath) noexcept;
    ~TextureResource() noexcept;
    GLuint m_texture[1];
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_TEXTURERESOURCE_H
