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

#include "../Scenes/sceneGraph.hpp"
#include "camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "../Shaders/Objects/ShaderPipeline.hpp"

using namespace std;

///
/// Renderer class
/// Renders the scene provided, from the point of view of the camera assigned to the object.
///
class renderer{
private:
    GLFWwindow*       p_window; // The window the viewport is rendering to
    
    GLuint            m_framebuffer;
    GLuint            m_framebufferTexture;
    GLuint            m_depthbuffer;
    // For completing 2 pass rendering for framebuffer effects
    GLuint            m_displayVao;
    GLuint            m_displayBuffer[2];
    
    glm::vec2 m_displayVertices[6] = {
        glm::vec2(-1.0f, 1.0f),
        glm::vec2(-1.0f,-1.0f),
        glm::vec2( 1.0f,-1.0f),
        glm::vec2(-1.0f, 1.0f),
        glm::vec2( 1.0f,-1.0f),
        glm::vec2( 1.0f, 1.0f)
    };
    
    glm::vec2 m_displayUvs[6] = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f)
    };
    
    float             m_aspect;                     // aspect ratio = width/height for exaple 4:3 or 16:9
    glm::mat4         m_proj_matrix;                // Will be used in handling perspective into the scene?
    
    ShaderPipeline*   p_framebufferPipeline;
    
    camera*           p_camera;
    sceneGraph*       p_scene;
    
    int m_windowWidth, m_windowHeight; // The current windows width and height
    
    GLint m_viewportX, m_viewportY; // Position of bottom left of viewport in x and y
    GLsizei m_viewportWidth, m_viewportHeight; // Width and height of the viewport
    
    glm::vec4 m_clearColour = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
public:
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
