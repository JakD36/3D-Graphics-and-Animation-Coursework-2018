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
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Lights/Lights.hpp"

#include "../Shaders/ShaderManager.h"
#include "buffers.h"

///
/// Renderer class
/// Renders the scene provided, from the point of view of the camera assigned to the object.
///
class Renderer{
private:
    GLFWwindow*       p_window; // The window the viewport is rendering to

    FramebufferBase* m_framebuffer;
    LightUniformBuffer m_lightUbo;

    int m_windowWidth, m_windowHeight; // The current windows width and height
    
    GLint m_viewportX, m_viewportY; // Position of bottom left of viewport in x and y
    GLsizei m_viewportWidth, m_viewportHeight; // Width and height of the viewport
    
    glm::vec4 m_clearColour = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
public:
    Renderer(GLFWwindow* window); // Requires a camera to view the scene, a window to render to, and a scene to draw
    ~Renderer();

    void SetWindowDimensions(int windowWidth, int windowHeight); // Used to update the Renderer the window has changed size
    void SetViewport(float x, float y, float width, float height);

    void Render(SceneGraph* scene);
    void RenderScene(SceneGraph *scene, int viewportX, int viewportY, int viewportWidth, int viewportHeight);
};

#endif /* Renderer_hpp */
