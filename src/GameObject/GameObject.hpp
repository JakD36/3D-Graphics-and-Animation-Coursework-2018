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

class Mesh;
class Material;
class Texture;
class Camera;
class Transform;

class GameObject {
public:
    Transform* m_transform;
    
    GameObject(Mesh*, Material*, Texture*, GLuint) noexcept;
    GameObject(std::string mesh, std::string mat, std::string tex, GLuint) noexcept;

    Mesh* m_mesh;
    Texture* m_texture;
    Material* m_material;
    GLuint m_program;
    
    void Render(Camera camera) noexcept;
};

#endif /* GameObject_hpp */
