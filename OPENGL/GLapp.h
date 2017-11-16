//
//  GLapp.h
//  OPENGL
//
//  Created by Jack Davidson on 26/09/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#ifndef GLapp_h
#define GLapp_h

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
#include "modelObject.h"
#include "modelObjectInst.h"
#include "modelObjectSingle.h"

void errorCallbackGLFW(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void debugGL();
static void APIENTRY openGLDebugCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const GLvoid* userParam);


class GLapp{
private:
    
    GLFWwindow*             window;
    int                     windowWidth = 640;
    int                     windowHeight = 480;
    float                   aspect;
    glm::mat4               proj_matrix;
    bool                    keyStatus[1024] = {false};
    unsigned int            nTriangles = 0;
    bool                    running = true;

    modelObjectSingle       torchObj;
    //modelObjectInst         pac;
    modelObjectSingle       room;
    
    vector<modelObject*> Objs;
    lightStruct lights[LIGHTSN];
    lightStruct light;
    
    // framebuffer
    GLuint            framebuffer;
    GLuint            framebufferTexture;
    GLuint            depthbuffer;
    GLuint            displayVao;
    GLuint            displayBuffer[2];
    std::vector < glm::vec2 > displayVertices;
    std::vector < glm::vec2 > displayUvs;
    GLuint            displayProgram;

    
    // Camera Variables
    int mouseX, mouseY;
    double lastX = 0, lastY = 0;
    GLfloat yaw=0, pitch=0;
    glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,1.0f);
    glm::vec3 cameraPos = glm::vec3(0.0f,1.6f,0.0f);    
    

public:
    
    
    GLapp();
    ~GLapp();
    
    void run();
    string readShader(string fileName);
    
    void endProgram();
    void setupRender();
    void startup();
    void update(double currentTime);
    void render(double currentTime);
    void hintsGLFW();
    void checkErrorShader(GLuint shader);
    
    void setKeyStatus(int key);
    void setWindowWidth(int w);
    void setWindowHeight(int w);
    void setAspect(float);
    void setProjMatrix(glm::mat4);
    
    void classerrorCallbackGLFW(int error, const char* description);
    void classkeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void classonResizeCallback(GLFWwindow* window, int w, int h);
    void classonKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void classonMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void classonMouseMoveCallback(GLFWwindow* window, double x, double y);
    void classonMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
};



#endif /* GLapp_h */
