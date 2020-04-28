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

class Mesh;
class Material;
class Texture;
class Camera;
class Transform;

class GameObject {
public:
    GameObject(const GameObject &go) noexcept;
    GameObject(Mesh*, Material*, Texture*, GLuint, Transform* parent = nullptr) noexcept;
    GameObject(std::string mesh, std::string mat, std::string tex, GLuint, Transform* parent = nullptr) noexcept;

    gsl::owner<Transform*> m_transform;

    Mesh* m_mesh;
    Texture* m_texture;
    Material* m_material;
    GLuint m_program;
    
    void Render(Camera camera) noexcept;
};

#endif /* GameObject_hpp */
