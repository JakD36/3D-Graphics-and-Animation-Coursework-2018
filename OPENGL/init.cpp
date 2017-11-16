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


glm::vec3 lightStruct::ia = glm::vec3(0.0f,1.0f,0.2f);

void GLapp::startup() {
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight; // ARE THESE BEING CONVERTED TO FLOATS?
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);

    torchObj = modelObjectSingle();
    torchObj.initModel("newTorch.obj","vs.glsl","fs.glsl");
    torchObj.initTexture("newTorchCol.ktx");
    torchObj.loadMat("newTorch.mtl");
    torchObj.getUniLocation();
    torchObj.position.y = 1.6f;
    torchObj.rotation = glm::vec3(0.0f,-90.0f,0.0f);
    
    room = modelObjectSingle();
    room.initModel("room.obj","vs.glsl","fs.glsl");
    room.initTexture("roomCol.ktx");
    room.loadMat("room.mtl");
    room.getUniLocation();
    
    lights[0].type = lightType::point;
    lights[0].position = glm::vec3(0.0f,2.0f,0.0f);
    lights[0].id = glm::vec3(1.0f,1.0f,1.0f);
    lights[0].is = glm::vec3(1.0f,1.0f,1.0f);
    
    lights[1].type = lightType::point;
    lights[1].position = glm::vec3(2.0f,0.5f,2.0f);
    lights[1].id = glm::vec3(0.5f,0.0f,0.0f);
    lights[1].is = glm::vec3(0.5f,0.0f,0.0f);
    
    lights[2].type = lightType::spot;
    lights[2].position = glm::vec3(0.0f,1.0f,0.0f);
    lights[2].direction = cameraFront;
    lights[2].id = glm::vec3(5.0f,5.0f,5.0f);
    lights[2].is = glm::vec3(1.0f,1.0f,1.0f);
        
    Objs.push_back(&torchObj);
    Objs.push_back(&room);
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glGenTextures(1,&framebufferTexture);
    
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,windowWidth,windowHeight,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    
    // filtering needed - future lecture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Depth buffer texture    - Need to attach depth too otherwise depth testing will not be performed.
    glGenRenderbuffers(1, &depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
    
    displayVertices.push_back(glm::vec2(-1.0f, 1.0f));
    displayVertices.push_back(glm::vec2(-1.0f,-1.0f));
    displayVertices.push_back(glm::vec2( 1.0f,-1.0f));
    displayVertices.push_back(glm::vec2(-1.0f, 1.0f));
    displayVertices.push_back(glm::vec2( 1.0f,-1.0f));
    displayVertices.push_back(glm::vec2( 1.0f, 1.0f));
    
    displayUvs.push_back(glm::vec2(0.0f, 1.0f));
    displayUvs.push_back(glm::vec2(0.0f, 0.0f));
    displayUvs.push_back(glm::vec2(1.0f, 0.0f));
    displayUvs.push_back(glm::vec2(0.0f, 1.0f));
    displayUvs.push_back(glm::vec2(1.0f, 0.0f));
    displayUvs.push_back(glm::vec2(1.0f, 1.0f));
    
    glGenBuffers(2,displayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 displayVertices.size()*sizeof(glm::vec2),
                 &displayVertices[0],
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 displayUvs.size()*sizeof(glm::vec2),
                 &displayUvs[0],
                 GL_STATIC_DRAW);

    
    glGenVertexArrays(1,&displayVao);
    glBindVertexArray(displayVao);
    glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    
    //load shaders
    displayProgram = glCreateProgram();
    
    string dvs_text = readShader("vs_display.glsl");
    const char* dvs_source = dvs_text.c_str();
    GLuint dvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(dvs, 1, &dvs_source, NULL);
    glCompileShader(dvs);
    checkErrorShader(dvs);
    glAttachShader(displayProgram, dvs);
    
    string dfs_text = readShader("fs_display.glsl");
    const char* dfs_source = dfs_text.c_str();
    GLuint dfs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dfs, 1, &dfs_source, NULL);
    glCompileShader(dfs);
    checkErrorShader(dfs);
    glAttachShader(displayProgram, dfs);
    
    glLinkProgram(displayProgram);
    glUseProgram(displayProgram);

    
}
