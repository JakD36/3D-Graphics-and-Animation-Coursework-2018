//
//  GameObject.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <gsl/pointers>
#include <vector>
#include <tuple>
#include "../RenderPass.h"
#include "../Mesh/Mesh.h"

class Material;
class Texture;
class Camera;
class Transform;
class RenderTask;

class GameObject {
private:
public:
    GameObject(const GameObject &go) noexcept;
    GameObject(std::string renderPass, std::string mesh, Transform* parent = nullptr) noexcept;
    gsl::owner<Transform*> m_transform;

    RenderTask* m_renderTask;
    Mesh m_mesh;
    
    void Render(Camera camera) noexcept;
};

#endif /* GameObject_hpp */
