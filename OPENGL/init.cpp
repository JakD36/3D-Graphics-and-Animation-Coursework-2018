//
//  init.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"


void GLapp::setupRender() {
    glfwSwapInterval(1);    // Ony render when synced (V SYNC)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);
}

void GLapp::hintsGLFW() {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);            // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void GLapp::startup() {
    torchObj = modelObject();
    torchObj.program = glCreateProgram();

    string vs_text = readShader("vs.txt");
    const char * vs_source = vs_text.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    checkErrorShader(vs);
    glAttachShader(torchObj.program, vs);

    string fs_text = readShader("fs.txt");
        const char * fs_source = fs_text.c_str();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fs_source, NULL);
        glCompileShader(fs);
        checkErrorShader(fs);
        glAttachShader(torchObj.program, fs);

    glGenVertexArrays(1,&torchObj.vao);
    glBindVertexArray(torchObj.vao);
    glGenBuffers(2,torchObj.buffer);
    glBindBuffer(GL_ARRAY_BUFFER, torchObj.buffer[0]);
    torchObj.load("Torch.obj");
    nTriangles = 2* torchObj.out_vertices.size()*sizeof(glm::vec3);
    cout<<"Vertices\t"<<torchObj.out_vertices.size()<<"\tUvs\t"<<torchObj.out_uvs.size()<<"\tnormals\t"<<torchObj.out_normals.size()<<endl;
    
    glBufferData(GL_ARRAY_BUFFER,
                                  torchObj.out_vertices.size()*sizeof(glm::vec3),
                                  &torchObj.out_vertices[0],
                                  GL_STATIC_DRAW);
                     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
                     glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, torchObj.buffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 torchObj.out_uvs.size()*sizeof(glm::vec2),
                                  &torchObj.out_uvs[0],
                                  GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

//    pac = modelObject();
//    pac.program = glCreateProgram();
//    glAttachShader(pac.program, vs);
//    glAttachShader(pac.program, fs);
//
//    glGenVertexArrays(1,&pac.vao);
//    glBindVertexArray(pac.vao);
//    glGenBuffers(2,pac.buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, pac.buffer[0]);
//    pac.load("Pacmannblend.obj");
//    nTriangles += 2* pac.out_vertices.size()*sizeof(glm::vec3);
//
//    glBufferData(GL_ARRAY_BUFFER,
//                 pac.out_vertices.size()*sizeof(glm::vec3),
//                 &pac.out_vertices[0],
//                 GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, torchObj.buffer[1]);
//    glBufferData(GL_ARRAY_BUFFER,
//                 pac.out_vertices.size()*sizeof(glm::vec3),
//                 &pac.out_vertices[0],
//                 GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//    glEnableVertexAttribArray(1);

    
    
    glGenTextures(1, torchObj.texture);
    string name = "TorchO.ktx";
    gli::texture tex = gli::load(name);
    if(tex.empty()){
        cout<<"Unable to load file "+name <<endl;
    }
    gli::gl texGL(gli::gl::PROFILE_GL33);
    gli::gl::format const texFormat = texGL.translate(tex.format(), tex.swizzles());
    //load and create a texture
    glBindTexture(GL_TEXTURE_2D, torchObj.texture[0]);
    glm::tvec3<GLsizei> const texExtent(tex.extent());
    GLsizei const texFaceTotal = static_cast<GLsizei>(tex.layers()*tex.faces());
    glTexStorage2D(GL_TEXTURE_2D,static_cast<GLint>(tex.levels()),texFormat.Internal,texExtent.x,texExtent.y);
    for(std::size_t Layer = 0;Layer<tex.layers();++Layer){
        for(std::size_t Face = 0;Face<tex.faces();++Face){
            for(std::size_t Level = 0; Level<tex.levels();++Level){
                glTexSubImage2D(GL_TEXTURE_2D,static_cast<GLint>(Level),0,0,texExtent.x,texExtent.y,texFormat.External,texFormat.Type,tex.data(Layer,Face,Level));
            }
        }
    }
    
    // This only works for 2D Textures...
    // Set the texture wrapping parameters (next lecture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering parameters (next lecture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate mipmaps (next lecture)
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glLinkProgram(torchObj.program);
    glUseProgram(torchObj.program);
//    glLinkProgram(pac.program);
//    glUseProgram(pac.program);
    
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight; // ARE THESE BEING CONVERTED TO FLOATS?
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
    torchObj.mv_location = glGetUniformLocation(torchObj.program, "mv_matrix");
    torchObj.proj_location = glGetUniformLocation(torchObj.program, "proj_matrix");
    torchObj.tex_location = glGetUniformLocation(torchObj.program, "tex");
//    pac.mv_location = glGetUniformLocation(pac.program, "mv_matrix");
//    pac.proj_location = glGetUniformLocation(pac.program, "proj_matrix");

    //    angle_location = glGetUniformLocation(program, "angles");
}
