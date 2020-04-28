//
//  GameObject.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "GameObject.hpp"
#include "../Utils/ProfilerService.h"
#include "../Lights/Lights.hpp"
#include "../ResourceManager/ResourceService.hpp"
#include <glm/gtx/transform.hpp>
#include "../Mesh/Mesh.hpp"
#include "../Material/Material.hpp"
#include "../Texture/Texture.hpp"
#include "../Views/Camera.hpp"
#include "../Transform.h"
#include "../Utils/DebugUtils.h"
#include <fstream>
#include <json.hpp>
#include "../Shaders/ShaderManager.h"

using namespace std;

vector<GameObjectRenderPass> GameObject::BuildRenderPass(string filepath)
{
    nlohmann::json js;
    fstream file(filepath);
    assertm(file.is_open(),"RenderPass Json file did not open.");
    file >> js;

    ShaderManager* sm = ShaderManager::GetInstance();

    nlohmann::json passes = js["pass"];
    vector<GameObjectRenderPass> output(passes.size());

    for(int i = 0; i < passes.size(); ++i)
    {
        auto pass = passes[i];
        auto shaders = pass["shader"];
        GLuint program = sm->RequestProgram(shaders["vert"],shaders["frag"]);

        std::vector<TextureShaderParam> textures;

        auto texArrayJs = pass["textures"];
        for(int i = 0; i < texArrayJs.size(); ++i)
        {
            auto texJs = texArrayJs[i];
            m_texture = ResourceService<Texture>::GetInstance()->Request(texJs["file"]);
            textures.push_back(TextureShaderParam
            {
                glGetUniformLocation(program,((string)texJs["key"]).c_str()) ,
                texJs["key"],
                m_texture->m_texture[0]
            });
        }
        auto matJs = pass["material"];
        m_material = ResourceService<Material>::GetInstance()->Request(matJs["file"]);

        vector<Uniformf> uniformf;
        auto floats = pass["float"];
        for(int i = 0; i < floats.size(); ++i)
        {
            auto f = floats[i];
            if(f["key"] == "shininess")
            {
                uniformf.push_back(Uniformf{
                    glGetUniformLocation(program,((string)f["key"]).c_str()),
                    f["key"],
                    m_material->m_shininess
                });
            }
            else{
                uniformf.push_back(Uniformf{
                        glGetUniformLocation(program,((string)f["key"]).c_str()),
                        f["key"],
                        f["value"]
                });
            }
        }

        vector<Uniform3fv> uniform3fv;
        auto vec3s = pass["vec3"];
        for(int i = 0; i < vec3s.size(); ++i)
        {
            auto v = vec3s[i];
            if(v["key"] == "ka")
            {
                uniform3fv.push_back(Uniform3fv{
                        glGetUniformLocation(program,((string)v["key"]).c_str()),
                        v["key"],
                        m_material->m_ka
                });
            }
            else if(v["key"] == "kd")
            {
                uniform3fv.push_back(Uniform3fv{
                        glGetUniformLocation(program,((string)v["key"]).c_str()),
                        v["key"],
                        m_material->m_kd
                });
            }
            else if(v["key"] == "ks")
            {
                uniform3fv.push_back(Uniform3fv{
                        glGetUniformLocation(program,((string)v["key"]).c_str()),
                        v["key"],
                        m_material->m_ks
                });
            }
            else{
                auto vec = v["value"];
                uniform3fv.push_back(Uniform3fv{
                        glGetUniformLocation(program,((string)v["key"]).c_str()),
                        v["key"],
                        glm::vec3(vec["x"],vec["y"],vec["z"])
                });
            }
        }

        vector<Uniform4fv> uniform4fv;
        auto vec4s = pass["vec4"];
        for(int i = 0; i < vec4s.size(); ++i)
        {
            auto v = vec4s[i];
            if(v["key"] == "ia")
            {
                uniform4fv.push_back(Uniform4fv{
                        glGetUniformLocation(program,((string)v["key"]).c_str()),
                        v["key"],
                        glm::vec4(ia,1.f)
                });
            }
            else{
                auto vec = v["value"];
                uniform4fv.push_back(Uniform4fv{
                        glGetUniformLocation(program,((string)v["key"]).c_str()),
                        v["key"],
                        glm::vec4(vec["x"],vec["y"],vec["z"],vec["w"])
                });
            }
        }

        output.push_back(GameObjectRenderPass{
            program,
            textures,
            uniformf,
            uniform3fv,
            uniform4fv
        });
    }
    return output;
}

GameObject::GameObject(const GameObject &go) noexcept
{
    m_transform = new Transform(go.m_transform);
    m_mesh = go.m_mesh;
    m_material = go.m_material;
    m_texture = go.m_texture;

    m_program = go.m_program;
    m_renderPass = go.m_renderPass;
}

GameObject::GameObject(Mesh* mesh, Material* mat, Texture* tex, GLuint shaderProgram, Transform* parent) noexcept{
    m_transform = new Transform(parent);
    m_mesh = mesh;
    m_material = mat;
    m_texture = tex;
    
    m_program = shaderProgram;
}

GameObject::GameObject(string renderPass, string meshPath, string materialPath, string texturePath, GLuint shaderProgram, Transform* parent) noexcept{
    PROFILE(profiler,"GO Init");

    m_transform = new Transform(parent);

    m_mesh = ResourceService<Mesh>::GetInstance()->Request(meshPath);

    m_renderPass = BuildRenderPass(renderPass);

    ENDPROFILE(profiler);
}

void GameObject::Render(Camera camera) noexcept{
    PROFILE(profiler,"GO Render");

    assertm(m_mesh != nullptr,"Mesh Cannot be null");
    assertm(m_material != nullptr,"Material Cannot be null");
    assertm(m_texture != nullptr,"Texture Cannot be null");

    glm::mat4 m = m_transform->BuildModelMatrix();
    glm::mat4 mvp = camera.ProjectionMatrix() * camera.BuildViewMat() * m;

    assertm(m_renderPass.size() > 0,"No RenderPasses have been defined...");

    for(int i = 0; i < m_renderPass.size(); ++i)
    {
        GameObjectRenderPass& pass = m_renderPass[i];
        glUseProgram(pass.m_program);

        glBindVertexArray(m_mesh->m_vao);

        glUniformMatrix4fv(glGetUniformLocation(m_program,"modelMatrix"), 1, GL_FALSE, &m[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(m_program,"mvp"), 1, GL_FALSE, &mvp[0][0]);

        glUniform3fv(glGetUniformLocation(m_program,"viewPosition"),1,&camera.GetPosition()[0]); // The camera position

        for(int j = 0; j < pass.m_textures.size(); ++j)
        {
            glActiveTexture(GL_TEXTURE0+j);
            glBindTexture(GL_TEXTURE_2D,pass.m_textures[j].m_texture);
            glUniform1i(pass.m_textures[j].m_location, 0);
        }

        for(int j = 0; j < pass.m_uniformf.size(); ++j)
        {
            glUniform1f(pass.m_uniformf[j].m_location, pass.m_uniformf[j].m_value);
        }

        for(int j = 0; j < pass.m_uniform3fv.size(); ++j)
        {
            glUniform3fv(pass.m_uniform3fv[j].m_location, 1, &pass.m_uniform3fv[j].m_value[0]);
        }

        for(int j = 0; j < pass.m_uniform4fv.size(); ++j)
        {
            glUniform4fv(pass.m_uniform4fv[j].m_location, 1, &pass.m_uniform4fv[j].m_value[0]);
        }

        glDrawArrays(GL_TRIANGLES, 0, m_mesh->m_vertCount);
    }

    ENDPROFILE(profiler);
}


