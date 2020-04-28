//
//  Texture.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "Texture.hpp"
#include "../Utils/DebugUtils.h"
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <gli/gli.hpp>

using namespace std;

Texture::Texture(string texturePath) noexcept
{
    glGenTextures(1, m_texture);
    gli::texture tex = gli::load(texturePath);

    assertm(!tex.empty(),("Could not find file " + texturePath));
    if(tex.empty()){
        cout<<"Unable to load file "+texturePath <<endl;
    }
    gli::gl texGL(gli::gl::PROFILE_GL33);
    gli::gl::format const texFormat = texGL.translate(tex.format(), tex.swizzles());
    //load and create a texture
    glBindTexture(GL_TEXTURE_2D, m_texture[0]);
    glm::tvec3<GLsizei> const texExtent(tex.extent());
    GLsizei const texFaceTotal = static_cast<GLsizei>(tex.layers()*tex.faces());
    glTexStorage2D(GL_TEXTURE_2D,static_cast<GLint>(tex.levels()),texFormat.Internal,texExtent.x,texExtent.y);
    for(std::size_t Layer = 0;Layer<tex.layers();++Layer){
        for(std::size_t Face = 0;Face<tex.faces();++Face){
            for(std::size_t Level = 0; Level<tex.levels();++Level){
                glTexSubImage2D(GL_TEXTURE_2D,static_cast<GLint>(Level),0,0,texExtent.x,texExtent.y,texFormat.External,texFormat.Type,tex.data(Layer,Face,Level));
            }
        }
    }
    
    // This only works for 2D Textures...
    // Set the texture wrapping parameters (next lecture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering parameters (next lecture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate mipmaps (next lecture)
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() noexcept
{
    glDeleteTextures(1,m_texture);
}
