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

class Texture{
public:
    Texture(std::string texturePath) noexcept;
    ~Texture() noexcept;
    GLuint m_texture[1];
};


#endif /* Texture_h */
