//
//  Renderer.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <vector>

#include "../Scenes/SceneGraph.hpp"
#include "Camera.hpp"

#include "../Utils/ProfileService.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include "../Lights/Lights.hpp"

#include "../Shaders/ShaderManager.h"

using namespace std;

///
/// Renderer class
/// Renders the scene provided, from the point of view of the camera assigned to the object.
///
class Renderer{
private:
    GLFWwindow*       p_window; // The window the viewport is rendering to

    GLuint            m_framebuffer;
    GLuint            m_framebufferTexture;
    GLuint            m_depthbuffer;

    // For completing 2 pass rendering for framebuffer effects
    GLuint            m_displayVao;
    GLuint            m_displayBuffer;

    glm::vec2 m_displayCoords[12] = { // Interleaved coordinates for displaying to a Quad
            glm::vec2(-1.0f, 1.0f), // v
            glm::vec2(0.0f, 1.0f), // uv
            glm::vec2(-1.0f,-1.0f), // v
            glm::vec2(0.0f, 0.0f), // uv
            glm::vec2( 1.0f,-1.0f), // v
            glm::vec2(1.0f, 0.0f), // uv
            glm::vec2(-1.0f, 1.0f), // v
            glm::vec2(0.0f, 1.0f), // uv
            glm::vec2( 1.0f,-1.0f), // v
            glm::vec2(1.0f, 0.0f), // uv
            glm::vec2( 1.0f, 1.0f),// v
            glm::vec2(1.0f, 1.0f) // uv
    };

    GLuint m_framebufferProgram;
    
    Camera*           p_camera;
    SceneGraph*       p_scene;
    
    int m_windowWidth, m_windowHeight; // The current windows width and height
    
    GLint m_viewportX, m_viewportY; // Position of bottom left of viewport in x and y
    GLsizei m_viewportWidth, m_viewportHeight; // Width and height of the viewport
    
    glm::vec4 m_clearColour = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
public:
    Renderer(GLFWwindow* window, SceneGraph* scene, Camera* viewCamera); // Requires a camera to view the scene, a window to render to, and a scene to draw
    void Render();

    Camera* GetCamera();

    // Allows for starting a new scene, changing environments, changing levels. Simply swap the scene
    void ChangeScene(SceneGraph* scene); // FIX: Need to implement some form of defensive programming to make sure a scene is actually provided
    
    void SetWindowDimensions(int windowWidth, int windowHeight); // Used to update the Renderer the window has changed size

    void SetViewport(float x, float y, float width, float height);
};

#endif /* Renderer_hpp */
