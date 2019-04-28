//
//  VertexShader.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "VertexShader.hpp"

VertexShader::VertexShader(string vsPath){
    
    ShaderLoader* shaderInst = ShaderLoader::GetInstance(); // Get the instance of the singleton to load the shader
    
    string vs_text = shaderInst->ReadShader(vsPath);
    const char * vs_source = vs_text.c_str();
    m_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_shader, 1, &vs_source, NULL);
    glCompileShader(m_shader);
    shaderInst->CheckErrorShader(m_shader);
}
