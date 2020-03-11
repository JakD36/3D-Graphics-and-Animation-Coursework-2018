//
//  Texture.h
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <gli/gli.hpp>
#include <glm/gtx/transform.hpp>
#include "../ResourceManager/ResourceService.hpp"

class Texture{
public:
    Texture(std::string texturePath);
    ~Texture();
    GLuint          m_texture[1];
};


#endif /* Texture_h */
