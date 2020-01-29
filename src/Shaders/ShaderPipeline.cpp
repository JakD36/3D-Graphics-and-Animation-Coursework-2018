//
//  ShaderPipeline.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "ShaderPipeline.hpp"

/*
void CheckProgramLog(GLuint program){
    // Get the length of the info log in the program
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    if (maxLength > 0) { // If the length is > 0, we have an error or warning from the linker
        // Init a string for it
        std::vector<GLchar> log(maxLength);
        // Get the log file
        glGetShaderInfoLog(program, maxLength, &maxLength, &log[0]);
        std::cout << "--------------Shader compilation error-------------\n";
        std::cout << log.data();
    }
}
*/

ShaderPipeline::ShaderPipeline(VertexShader* vs, FragShader* fs){
    
    m_program = glCreateProgram();  // Create the program, for this model, to attach the shaders to
    
    glAttachShader(m_program, vs->m_shader);
    glAttachShader(m_program, fs->m_shader);
    
    glLinkProgram(m_program);

    /*GLint isLinked = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, (int *)&isLinked);

    if(isLinked == GL_FALSE)
        printf("Error program did not link");

    CheckProgramLog(m_program);*/
}

ShaderPipeline::ShaderPipeline(string vert, string frag){
    
    m_program = glCreateProgram();  // Create the program, for this model, to attach the shaders to
    
    glAttachShader(m_program, ResourceService<VertexShader>::GetInstance()->Request(vert)->m_shader);
    glAttachShader(m_program, ResourceService<FragShader>::GetInstance()->Request(frag)->m_shader);
    
    glLinkProgram(m_program);

    /*GLint isLinked = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, (int *)&isLinked);

    if(isLinked == GL_FALSE)
        printf("Error program did not link");

    CheckProgramLog(m_program);*/
}
