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
#include "../GameObjectRenderPass.h"

class Mesh;
class Material;
class Texture;
class Camera;
class Transform;

class GameObject {
private:
    struct FileInfo
    {
        std::string path;
        time_t lastModified;
    };
    FileInfo m_fileInfo;
    std::string m_meshPath;
    std::vector<GameObjectRenderPass> BuildRenderPass(std::string filepath, std::string meshpath);
public:
    GameObject(const GameObject &go) noexcept;
    GameObject(std::string renderPass, std::string mesh, Transform* parent = nullptr) noexcept;
    void UpdateFile() noexcept;
    std::vector<GameObjectRenderPass> m_renderPass;

    gsl::owner<Transform*> m_transform;

    Mesh* m_mesh;
    Texture* m_texture;
    Material* m_material;
    GLuint m_program;
    
    void Render(Camera camera) noexcept;
};

#endif /* GameObject_hpp */
