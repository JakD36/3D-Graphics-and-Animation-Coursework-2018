//
//  Texture.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "Texture.hpp"
#include <vector>
#include <GL/glew.h>

Texture::Texture(std::string filepath)
{
    m_manager = ResourceManager<TextureResource>::GetInstance();
    m_key = m_manager->Request(filepath);
}
Texture::Texture(const Texture &cp)
{
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
}

Texture::~Texture(){
    m_manager->Dispose(m_key);
}

GLuint* Texture::GetTexture(){
    return m_manager->m_data.At(m_key).m_texture;
}