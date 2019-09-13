//
//  Renderer.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Renderer.hpp"

static bool init = false;

// Return the camera for use outwith this object, to set/get camera position.
Camera* Renderer::GetCamera(){
    return p_camera;
}


void Renderer::SetViewport(float x, float y, float width, float height){
    m_viewportX = x;
    m_viewportY = y;
    m_viewportWidth = width;
    m_viewportHeight = height;

    // Calculate proj_matrix for the first time.
    m_aspect = (float)width / (float)height;
    m_proj_matrix =  glm::perspective(glm::radians(50.0f), m_aspect, 0.1f, 1000.0f);
}

void Renderer::SetWindowDimensions(int windowWidth, int windowHeight){
    this->m_windowWidth = windowWidth;
    this->m_windowHeight = windowHeight;
    
    
    // Update viewport so its size is appropriate for the new window!
    int width, height;
    glfwGetFramebufferSize(p_window, &width, &height);
//    SetViewport(width,height);
    m_aspect = (float)width / (float)height;
    m_proj_matrix = glm::perspective(glm::radians(50.0f),m_aspect,0.1f,1000.0f);
}


// Initialise the Renderer for this viewport
Renderer::Renderer(GLFWwindow* window, SceneGraph* scene, Camera* viewCamera){
    
    // Assign the variables to the object
    this->p_scene = scene;
    this->p_camera = viewCamera;
    this->p_window = window;
    
    // Grab the window dimensions for the current window, saves passing too many arguments to the constructor
    glfwGetWindowSize(p_window, &m_windowWidth, &m_windowHeight);
    
    // Calculate proj_matrix for the first time.
    m_aspect = (float)m_windowWidth / (float)m_windowHeight;
    m_proj_matrix = glm::perspective(glm::radians(50.0f), m_aspect, 0.1f, 1000.0f);
    
    // On high DPI, there are a higher number of pixels in the window than the length of the window, so we need to use the frameWidth and height,
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);
    
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    //Setup the framebuffer using the following code taken from the the lecture notes and code
    
    glGenFramebuffers(1,&m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer);
    glGenTextures(1,&m_framebufferTexture);
    
    glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,frameWidth,frameHeight,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    
    // filtering needed - future lecture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Depth buffer texture    - Need to attach depth too otherwise depth testing will not be performed.
    glGenRenderbuffers(1, &m_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, frameWidth, frameHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbuffer);
    
    glGenBuffers(2,m_displayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_displayBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 6 * sizeof(glm::vec2),
                 &m_displayVertices[0],
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_displayBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 6 * sizeof(glm::vec2),
                 &m_displayUvs[0],
                 GL_STATIC_DRAW);
    
    glGenVertexArrays(1,&m_displayVao);
    glBindVertexArray(m_displayVao);
    glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    
    
    VertexShader* displayVs = new VertexShader("Shaders/vs_display.glsl");
    FragShader* displayFs = new FragShader("Shaders/fs_display.glsl");
    p_framebufferPipeline = new ShaderPipeline(displayVs,displayFs);
}


void Renderer::Render(){
    
    // So now to render to the framebuffer texture instead of screen
    glBindFramebuffer(GL_FRAMEBUFFER,m_framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_framebufferTexture,0);
    
    int frameWidth, frameHeight;//, frameLeft, frameRight, frameBottom, frameTop;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);
    // Convert all our projected coordinates to screen coordinates for the texture
    
    glViewport(0,0, frameWidth, frameHeight);
    
    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, frameWidth, frameHeight);
    
    glClearBufferfv(GL_COLOR, 0, &m_clearColour[0]);
    static const GLfloat one = 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glm::vec3 camPosition = p_camera->GetPosition();
    
    // To create our camera, we use the lookAt function generate the viewMatrix
    // It takes 3 inputs, the position of the camera, the point in space it is facing and which direction is up, so its orientated properly
    glm::mat4 viewMatrix = glm::lookAt(camPosition,                       // eye
                                       camPosition+p_camera->GetFront(),           // centre, we need to use the pos+cameraFront to make sure its pointing to the right point in space
                                       glm::vec3(0.0f, 1.0f, 0.0f));    // up
    
    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    vector<GameObject*> Objs = p_scene->GetObjs();
    lightStruct* p_lights = p_scene->GetLights();
    lightStruct lights[LIGHTSN];
    for(int n = 0; n < LIGHTSN; n++){
        lights[n] = *(p_lights+n);
    }
    
    // Workaround for mojave issue
    // FIX: Find permanent solution
    if(!init){
        glfwHideWindow(p_window);
        glfwShowWindow(p_window);
        init = true;
    }

    for(int n = 0;n<Objs.size();n++){
        Objs[n]->Render(m_proj_matrix,viewMatrix,lights,camPosition); 
    }
    
    // SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
    glScissor(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); //not needed as we are just displaying a single quad
    glUseProgram(p_framebufferPipeline->m_program);
    glBindVertexArray(m_displayVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}
