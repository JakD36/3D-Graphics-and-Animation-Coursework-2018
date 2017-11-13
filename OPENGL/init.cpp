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

GLfloat lightStruct::ka = 0.1;
glm::vec3 lightStruct::ia = glm::vec3(0.0f,0.6f,0.2f);

void GLapp::startup() {
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight; // ARE THESE BEING CONVERTED TO FLOATS?
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);

    
    torchObj = modelObjectSingle();
    torchObj.initModel("newTorch.obj","vs.glsl","fs.glsl");
    torchObj.initTexture("newTorchCol.ktx");
    torchObj.getUniLocation();
    torchObj.position.y = 1.6f;
    torchObj.rotation = glm::vec3(0.0f,-90.0f,0.0f);
//    torchObj.rotation.y = -90.0f;
    
    room = modelObjectSingle();
    room.initModel("room.obj","vs.glsl","fs.glsl");
    room.initTexture("roomCol.ktx");
    room.getUniLocation();
    
    light.kd = 5.0;
    light.id = glm::vec3(1.0f,1.0f,1.0f);
    light.is = glm::vec3(1.0f,1.0f,1.0f);
    light.ks = 0.1;
    light.shininess = 32.0f;

//    pac = modelObjectInst();
//    pac.initModel("room.obj","vs.txt","fs.txt");
//    pac.initTexture("roomCol.ktx");
//    pac.getUniLocation();
//
//    pac.position.push_back(glm::vec3(10.0f,0.0f,0.0f));
//    pac.position.push_back(glm::vec3(-10.0f,0.0f,0.0f));
//    pac.position.push_back(glm::vec3(0.0f,10.0f,0.0f));
//    pac.position.push_back(glm::vec3(0.0f,-10.0f,0.0f));
//    pac.position.push_back(glm::vec3(0.0f,0.0f,10.0f));
//    pac.position.push_back(glm::vec3(0.0f,0.0f,-10.0f));
//
//    pac.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
//    pac.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
//    pac.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
//    pac.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
//    pac.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
//    pac.rotation.push_back(glm::vec3(0.0f,0.0f,0.0f));
//
//    pac.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
//    pac.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
//    pac.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
//    pac.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
//    pac.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));
//    pac.scale.push_back(glm::vec3(1.0f,1.0f,1.0f));

    
    Objs.push_back(&torchObj);
    Objs.push_back(&room);
//    Objs.push_back(&pac);
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}
