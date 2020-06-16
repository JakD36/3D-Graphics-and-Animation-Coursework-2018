//
//  Texture.h
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <string>
#include <GL/glew.h>
#include "TextureResource.h"
#include "../ResourceManager/ResourceManager.h"

class Texture{
private:
    size_t m_key;
    ResourceManager<TextureResource>* m_manager;
public:
    Texture(std::string filepath);
    Texture(const Texture &cp);
    Texture& operator=(const Texture &cp);
    ~Texture();

    GLuint* GetTexture();
};


#endif /* Texture_h */
