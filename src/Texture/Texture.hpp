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

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <gli/gli.hpp>
#include <GLM/gtx/transform.hpp>

#include "../Shaders/shaderLoader.hpp"

class Texture{
public:
    Texture(string texturePath);
    GLuint          m_texture[1];                     //
};


#endif /* Texture_h */
