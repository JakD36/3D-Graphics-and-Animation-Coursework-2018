//
//  ShaderPipeline.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "ShaderPipeline.hpp"

ShaderPipeline::ShaderPipeline(VertexShader* vs, FragShader* fs){
    
    m_program = glCreateProgram();  // Create the program, for this model, to attach the shaders to
    
    glAttachShader(m_program, vs->m_shader);
    glAttachShader(m_program, fs->m_shader);
    
    glLinkProgram(m_program);
}
