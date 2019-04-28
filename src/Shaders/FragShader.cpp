//
//  FragShader.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "FragShader.hpp"

FragShader::FragShader(string fsPath){
    
    ShaderLoader* shaderInst = ShaderLoader::GetInstance(); // Get the instance of the singleton to load the shader
    
    // Fragment shader
    string fs_text = shaderInst->ReadShader(fsPath);
    const char * fs_source = fs_text.c_str();
    m_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_shader, 1, &fs_source, NULL);
    glCompileShader(m_shader);
    shaderInst->CheckErrorShader(m_shader);
}
