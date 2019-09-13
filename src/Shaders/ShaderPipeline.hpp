//
//  ShaderPipeline.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef ShaderPipeline_hpp
#define ShaderPipeline_hpp

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

#include "ShaderLoader.hpp"
#include "VertexShader.hpp"
#include "FragShader.hpp"

#include "../ResourceManager/ResourceService.hpp"

class ShaderPipeline{
public:
    GLuint          m_program;                        // Program to attach our shaders to

    ShaderPipeline(VertexShader* vs, FragShader* fs);
    ShaderPipeline(string vert, string frag);
    
};

#endif /* ShaderPipeline_hpp */
