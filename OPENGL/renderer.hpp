//
//  renderer.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <gli/gli.hpp>

#include "Observer.hpp"
#include "sceneGraph.hpp"

class renderer: public Observer{
private:
    // Our private variables
    sceneGraph* scene;
    
    
    
    // framebuffer variables, these all handle the framebuffer
    GLuint            framebuffer;
    GLuint            framebufferTexture;
    GLuint            depthbuffer;
    GLuint            displayVao;
    GLuint            displayBuffer[2];
    std::vector < glm::vec2 > displayVertices;
    std::vector < glm::vec2 > displayUvs;
    GLuint            displayProgram;
    
    int windowWidth;
    int windowHeight;
    
public:
    virtual void update();
    renderer(sceneGraph* scene,int windowWidth, int windowHeight);
    void endProgram();                      // cleans up and closes OpenGL
    void setupRender();                     // along with hintsGLFW sets up some window hints for running openGL
    void startup();                         // loads models, textures, material properties. sets up the lights and the framebuffer texture to render to
    
    void hintsGLFW();
    void setWindowSize(int windowWidth, int windowHeight);
};

#endif /* renderer_hpp */
