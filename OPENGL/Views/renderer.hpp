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

/*
 renderer class
 
 renders the scene provided, from the point of view of the camera assigned to the object.
 By setting the viewport position, width and height can render the same scene from multiple cameras by using multiple renderer objects.
*/
class renderer{
private:
    
    GLFWwindow*       window; // The window the viewport is rendering to
    
    GLuint            framebuffer;
    GLuint            framebufferTexture;
    GLuint            depthbuffer;
    
    // For completing 2 pass rendering for framebuffer effects
    GLuint            displayVao;
    GLuint            displayBuffer[2];
    std::vector < glm::vec2 > displayVertices;
    std::vector < glm::vec2 > displayUvs;
    GLuint            displayProgram;
    float                   aspect;                     // aspect ratio = width/height for exaple 4:3 or 16:9
    glm::mat4               proj_matrix;                // Will be used in handling perspective into the scene?
    
    
    camera* viewCamera; // The camera that this viewport is looking from, contains information on position in world space, direction it is facing
    sceneGraph* scene;  // The scene that this viewport is rendering
    
    int windowWidth, windowHeight; // The current windows width and height
    
    
    GLint viewportX, viewportY; // Position of bottom left of viewport in x and y
    GLsizei viewportWidth, viewportHeight; // Width and height of the viewport
    
public:
    // Constructor
    renderer(GLFWwindow* window, sceneGraph* scene, camera* viewCamera); // Requires a camera to view the scene, a window to render to, and a scene to draw
   
    
    void render(); // Render the scene on screen
    
    // Accessors
    camera* getCamera();
    
    // Mutators
    // Allows for starting a new scene, changing environments, changing levels. Simply swap the scene
    void changeScene(sceneGraph* scene); // FIX: Need to implement some form of defensive programming to make sure a scene is actually provided
    
    void setWindowDimensions(int windowWidth, int windowHeight); // Used to update the renderer the window has changed size
    
//    For use with creating multiple viewports within 1 window, currently viewports are a bit off 
    void setViewport(float x, float y, float width, float height); 
};

#endif /* renderer_hpp */
