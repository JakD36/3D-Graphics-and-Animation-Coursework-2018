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

class Mesh;
class Material;
class Texture;
class Camera;
class Transform;

struct TextureShaderParam
{
    GLint m_location;
    std::string m_key;
    GLuint m_texture;
};

struct Uniformf
{
    GLint m_location;
    std::string m_key;
    float m_value;
};

struct Uniform3fv
{
    GLint m_location;
    std::string m_key;
    glm::vec3 m_value;
};

struct Uniform4fv
{
    GLint m_location;
    std::string m_key;
    glm::vec4 m_value;
};

struct GameObjectRenderPass // TODO: Handle using previous render in next
{
public:
    GLuint m_program;
    GLenum m_cullFace;
    std::vector<TextureShaderParam> m_textures; // location, key, texture
    std::vector<Uniformf> m_uniformf; // location, key, val
    std::vector<Uniform3fv> m_uniform3fv; // location, key, val
    std::vector<Uniform4fv> m_uniform4fv; // location, key, val
};

class GameObject {
private:
    std::vector<GameObjectRenderPass> BuildRenderPass(std::string filepath, std::string meshpath);
public:
    GameObject(const GameObject &go) noexcept;
    GameObject(Mesh*, Material*, Texture*, GLuint program, Transform* parent = nullptr) noexcept;
    GameObject(std::string renderPass, std::string mesh, Transform* parent = nullptr) noexcept;

    std::vector<GameObjectRenderPass> m_renderPass;

    gsl::owner<Transform*> m_transform;

    Mesh* m_mesh;
    Texture* m_texture;
    Material* m_material;
    GLuint m_program;
    
    void Render(Camera camera) noexcept;
};

#endif /* GameObject_hpp */
