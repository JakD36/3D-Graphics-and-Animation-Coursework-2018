//
//  Renderer.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 23/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <glm/glm.hpp>
#include <memory>
#include "Lights/Lights.hpp"

class SceneGraph;
class RenderCommandProcessor;
class Window;

///
/// Renderer class
/// Renders the scene provided, from the point of view of the camera assigned to the object.
///
class Renderer{
private:
    LightUniformBuffer m_lightUbo;
    int m_windowWidth, m_windowHeight; // The current windows width and height

    std::unique_ptr<RenderCommandProcessor> m_cmdProc;

public:
    Renderer(Window* window) noexcept;
    ~Renderer() noexcept;

    void Render(Window* window, SceneGraph* scene) noexcept;
};

#endif /* Renderer_hpp */
