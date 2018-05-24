//
//  renderer.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <stdio.h>
#include <vector>

#include "sceneGraph.hpp"
#include "camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>


using namespace std;

class renderer{
private:
    GLFWwindow* window;
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
    float                   aspect;                     // aspect ratio = width/height for exaple 4:3 or 16:9
    glm::mat4               proj_matrix;                // Will be used in handling perspective into the scene?
    camera* myCamera;
    sceneGraph* scene;
    
    float viewportX, viewportY, viewportWidth, viewportHeight;
    
public:
    renderer(GLFWwindow* window, sceneGraph* scene, camera* myCamera, int windowWidth, int windowHeight);
    void render();
    camera* getCamera();
    void setViewport(float x, float y, float width, float height);
};

#endif /* renderer_hpp */
