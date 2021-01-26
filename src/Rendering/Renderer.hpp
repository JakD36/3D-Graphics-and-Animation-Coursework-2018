//
//  Renderer.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include "Lights/Lights.hpp"

class SceneGraph;

///
/// Renderer class
/// Renders the scene provided, from the point of view of the camera assigned to the object.
///
class Renderer{
private:
    GLFWwindow*       p_window; // The window the viewport is rendering to
    LightUniformBuffer m_lightUbo;
    int m_windowWidth, m_windowHeight; // The current windows width and height
    
public:
    Renderer(GLFWwindow* window) noexcept;
    ~Renderer() noexcept;

    void SetViewport(float x, float y, float width, float height) noexcept;

    void Render(GLFWwindow* window,SceneGraph* scene) noexcept;
};

#endif /* Renderer_hpp */
