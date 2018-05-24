//
//  renderer.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "renderer.hpp"

renderer::renderer(GLFWwindow* window, sceneGraph* scene, camera* myCamera, int windowWidth, int windowHeight){
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->window = window;
    this->scene = scene;
    this->myCamera = myCamera;
    
    
    viewportX = 0;
    viewportY = 0;
    viewportWidth = windowWidth;
    viewportHeight = windowHeight;
    
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight;
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    //Setup the framebuffer using the following code taken from the the lecture notes and code
    
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
    
    shaderLoader* shaderInst = shaderLoader::getInstance();
    
    string dvs_text = shaderInst->readShader("Shaders/vs_display.glsl");
    const char* dvs_source = dvs_text.c_str();
    GLuint dvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(dvs, 1, &dvs_source, NULL);
    glCompileShader(dvs);
    shaderInst->checkErrorShader(dvs);
    glAttachShader(displayProgram, dvs);
    
    string dfs_text = shaderInst->readShader("Shaders/fs_display.glsl");
    const char* dfs_source = dfs_text.c_str();
    GLuint dfs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dfs, 1, &dfs_source, NULL);
    glCompileShader(dfs);
    shaderInst->checkErrorShader(dfs);
    glAttachShader(displayProgram, dfs);
    
    glLinkProgram(displayProgram);
    glUseProgram(displayProgram);

}


void renderer::render(){
    // So now to render to the framebuffer texture instead of screen
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,framebufferTexture,0);
    
    glm::vec4 black = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
//    glViewport(viewportX, viewportY, viewportWidth, viewportHeight); // Convert all our projected coordinates to screen coordinates for the texture
    glViewport(0.0f, 0.0f, windowWidth, windowHeight);
    glClearBufferfv(GL_COLOR, 0, &black[0]);
    static const GLfloat one = 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glm::vec3 camPosition = myCamera->getPosition();
    
    // To create our camera, we use the lookAt function generate the viewMatrix
    // It takes 3 inputs, the position of the camera, the point in space it is facing and which direction is up, so its orientated properly
    glm::mat4 viewMatrix = glm::lookAt(camPosition,                       // eye
                                       camPosition+myCamera->getFront(),           // centre, we need to use the pos+cameraFront to make sure its pointing to the right point in space
                                       glm::vec3(0.0f, 1.0f, 0.0f));    // up
    
    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    vector<modelObject*> Objs = scene->getObjs();
    lightStruct* plight = scene->getLights();
    lightStruct lights[LIGHTSN];
    for(int n = 0; n < LIGHTSN; n++){
        lights[n] = *(plight+n);
    }
    
    
    for(int n = 0;n<Objs.size();n++){
        Objs[n]->setupRender(proj_matrix,lights,camPosition);
        Objs[n]->render(proj_matrix,viewMatrix,lights,camPosition);
    }
    
    // SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER,0);
//    glViewport(-windowWidth*2, -windowHeight*2, windowWidth*4, windowHeight*4);
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); //not needed as we are just displaying a single quad
    glUseProgram(displayProgram);
    glBindVertexArray(displayVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    
}

camera* renderer::getCamera(){
    return myCamera;
}

void renderer::setViewport(float x, float y, float width, float height){
    viewportX = x;
    viewportY = y;
    viewportWidth = width;
    viewportHeight = height;
    
    // Calculate proj_matrix for the first time.
    aspect = (float)width / (float)height;
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
}