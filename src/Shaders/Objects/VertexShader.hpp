//
//  VertexShader.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef VertexShader_hpp
#define VertexShader_hpp

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

#include "../shaderLoader.hpp"

class VertexShader{
public:
    VertexShader(string vsPath);
    
    GLuint m_shader;
};

#endif /* VertexShader_hpp */
