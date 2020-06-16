//
// Created by Jack Davidson on 14/06/2020.
//

#include "TextureResource.h"

#include "../Utils/DebugUtils.h"
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <gli/gli.hpp>

using namespace std;

TextureResource::TextureResource(string texturePath) noexcept  : Resource(texturePath)
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

TextureResource::~TextureResource() noexcept
{
    glDeleteTextures(1,m_texture); // TODO: Fix currently as soon as we copy our resource into our sparse vector we call the destructor and delete the texture
}

TextureResource::TextureResource(TextureResource &&mv) : Resource(mv.m_key){
    *this = std::move(mv);
}
TextureResource& TextureResource::operator=(TextureResource &&mv){

    m_key = mv.m_key;
    m_lastModified = mv.m_lastModified;
    m_count = mv.m_count;
    mv.m_key = "";
    mv.m_lastModified = 0;
    mv.m_count = 0;

    m_texture[0] = mv.m_texture[0];
    mv.m_texture[0] = 0;
    return *this;
}

TextureResource::TextureResource(TextureResource &cp) : Resource(cp.m_key){}
TextureResource& TextureResource::operator=(TextureResource &cp){}
