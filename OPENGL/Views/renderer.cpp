//
//  renderer.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "renderer.hpp"

static bool init = false;

// Return the camera for use outwith this object, to set/get camera position.
camera* renderer::getCamera(){
    return viewCamera;
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

void renderer::setWindowDimensions(int windowWidth, int windowHeight){
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    
    
    // Update viewport so its size is appropriate for the new window!
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
//    setViewport(width,height);
    aspect = (float)width / (float)height;
    proj_matrix = glm::perspective(glm::radians(50.0f),aspect,0.1f,1000.0f);
}


// Initialise the renderer for this viewport
renderer::renderer(GLFWwindow* window, sceneGraph* scene, camera* viewCamera){
    
    // Assign the variables to the object
    this->scene = scene;
    this->viewCamera = viewCamera;
    this->window = window;
    
    // Grab the window dimensions for the current window, saves passing too many arguments to the constructor
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight;
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
    
    // On high DPI, there are a higher number of pixels in the window than the length of the window, so we need to use the frameWidth and height,
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(window, &frameWidth, &frameHeight);
    
    
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
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,frameWidth,frameHeight,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    
    // filtering needed - future lecture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Depth buffer texture    - Need to attach depth too otherwise depth testing will not be performed.
    glGenRenderbuffers(1, &depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
    
    // The creates a polygon that the image will be rendered to on first pass
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
    
    
    VertexShader* displayVs = new VertexShader("Shaders/vs_display.glsl");
    FragShader* displayFs = new FragShader("Shaders/fs_display.glsl");
    framebufferPipeline = new ShaderPipeline(displayVs,displayFs);
}


void renderer::render(){
    
    // So now to render to the framebuffer texture instead of screen
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,framebufferTexture,0);
    
    glm::vec4 black = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
    
    int frameWidth, frameHeight;//, frameLeft, frameRight, frameBottom, frameTop;
    glfwGetFramebufferSize(window, &frameWidth, &frameHeight);
    // Convert all our projected coordinates to screen coordinates for the texture
    
    glViewport(0,0, frameWidth, frameHeight);
    
    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, frameWidth, frameHeight);
    
    glClearBufferfv(GL_COLOR, 0, &black[0]);
    static const GLfloat one = 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glm::vec3 camPosition = viewCamera->getPosition();
    
    // To create our camera, we use the lookAt function generate the viewMatrix
    // It takes 3 inputs, the position of the camera, the point in space it is facing and which direction is up, so its orientated properly
    glm::mat4 viewMatrix = glm::lookAt(camPosition,                       // eye
                                       camPosition+viewCamera->getFront(),           // centre, we need to use the pos+cameraFront to make sure its pointing to the right point in space
                                       glm::vec3(0.0f, 1.0f, 0.0f));    // up
    
    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    vector<modelObject*> Objs = scene->getObjs();
    lightStruct* plight = scene->getLights();
    lightStruct lights[LIGHTSN];
    for(int n = 0; n < LIGHTSN; n++){
        lights[n] = *(plight+n);
    }
    
    // Workaround for mojave issue
    // FIX: Find permanent solution
    if(!init){
        glfwHideWindow(window);
        glfwShowWindow(window);
        init = true;
    }

    for(int n = 0;n<Objs.size();n++){
        Objs[n]->setupRender(proj_matrix,lights,camPosition); 
        Objs[n]->render(proj_matrix,viewMatrix,lights,camPosition);
    }
    
    scene->m_gameObject->Render(proj_matrix,viewMatrix,lights,camPosition);

    
    
    
    // SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glViewport(viewportX,viewportY, viewportWidth, viewportHeight);
    glScissor(viewportX,viewportY, viewportWidth, viewportHeight);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); //not needed as we are just displaying a single quad
    glUseProgram(framebufferPipeline->m_program);
    glBindVertexArray(displayVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}
