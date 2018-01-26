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

// Our prototypes for functions used throughout the program, mainly the callbacks to handle user input
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
    // Our private variables
    GLFWwindow*             window;                     // Window the app will be displayed in
    int                     windowWidth = 640;          // width of the window
    int                     windowHeight = 480;         // height of the window
    float                   aspect;                     // aspect ratio = width/height for exaple 4:3 or 16:9
    glm::mat4               proj_matrix;                // Will be used in handling perspective into the scene?
    bool                    keyStatus[1024] = {false};  // Stores if the keys have been presed or not
    bool                    running = true;             // is the app running yes or no
    
    // This specifically is for the torch, attached to the player.
    float sphereRadius = 0.4;                           // Its sitting 0.4 m away from the camera
    float yawOffset = 30;                               // Its offset from the camera by the 30 degrees in the yaw
    float pitchOffset = 20;                             // Its offset from the camera by the 20 degrees in the pitch

    
    // Objects to be added into the system
    modelObjectSingle       torchObj;
    modelObjectSingle       front;
    modelObjectInst         planks;
    modelObjectSingle       floor;
    modelObjectInst         wall;
    modelObjectSingle       back;
    modelObjectSingle       roof;
    modelObjectInst         beam;
    modelObjectSingle       bulb;
    modelObjectSingle       wire;
    modelObjectSingle       table;
    modelObjectSingle       lamp;
    
    
    vector<modelObject*> Objs;  // This is a vector of pointers to the objects in the scene, this allows us to render everything in the
                                // scene by adding to this vector of objects no matter if its a modelObject single or instanced.
                                // This is polymorphism
    lightStruct lights[LIGHTSN];// Creates our array of lightStructs to store details on all the lights in the scene.
    
    // framebuffer variables, these all handle the framebuffer
    GLuint            framebuffer;
    GLuint            framebufferTexture;
    GLuint            depthbuffer;
    GLuint            displayVao;
    GLuint            displayBuffer[2];
    std::vector < glm::vec2 > displayVertices;
    std::vector < glm::vec2 > displayUvs;
    GLuint            displayProgram;
    
    
    bool LMBClicked = false;            // Is the left mouse button clicked
    bool RMBClicked = false;            // Is the right mouse button clicked
    double          prevTime = 0;       // time at the previous frame
    
    // These are the details for the swinging light above the player, it is a pendulum
    float lightRadius = 0.25f;          // The radius at which the light swings
    float lightYaw = 0.0f;              // instantiate its yaw and give its initial yaw as 0
    float lightPitch = -20.0f;          // instantiate its pitch and give its initial pitch of -20 so that it can start with a 0 velocity and still move
    double          v = 0;              // instantiate the lights velocity and start it with 0, this way it starts moving as gravity starts pulling it down
    
    
    
    // Camera Variables
    int mouseX, mouseY;                 // Position of mouse on screen in x and y axis
    double lastX = 0, lastY = 0;        // position of mouse on screen in x and y for the last frame
    GLfloat yaw=0, pitch=0;             // the yaw and pitch angles to be calculated from the change in mouse position
    glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,1.0f);  // the direction the camera is facing
    glm::vec3 cameraPos = glm::vec3(0.0f,1.6f,0.0f);    // The cameras position in the world space
    

public:
    
    
    GLapp();
    ~GLapp();
    
    void run();                             // Handles running the game loop
    string readShader(string fileName);     // Reads the GLSL shaders so they can be compiled and attached to the programs for each model
    
    void endProgram();                      // cleans up and closes OpenGL
    void setupRender();                     // along with hintsGLFW sets up some window hints for running openGL
    void startup();                         // loads models, textures, material properties. sets up the lights and the framebuffer texture to render to
    void update(double currentTime);        // handles updating objects based on the inputs from the user, or from interaction from other objects
    void render(double currentTime);        // loops through all the objects to be rendered on screen, then does a second pass through the framebuffer to render to screen with optional screen effect
    void hintsGLFW();
    void checkErrorShader(GLuint shader);
    
    glm::vec3 posOnSphere(float radius,float yaw,float pitch); // Calculates the cartesian coordinates ie x,y,z from the spherical coordinates or radius, yaw and pitch
    
    // My workarounds for callbacks to work with the app as a class, these are just called by the actual callbacks when the user interacts with the system.
    void classerrorCallbackGLFW(int error, const char* description);
    void classkeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void classonResizeCallback(GLFWwindow* window, int w, int h);
    void classonKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void classonMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void classonMouseMoveCallback(GLFWwindow* window, double x, double y);
    void classonMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    // Simply prints out a vector with each of the strings below before the corresponding value in the vec3
    void printVec3(glm::vec3,string,string,string);
    
};



#endif /* GLapp_h */
