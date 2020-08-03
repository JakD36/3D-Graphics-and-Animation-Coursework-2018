//
// Created by Jack Davidson on 10/05/2020.
//

#include "RenderPass.h"
#include "../Shaders/ShaderManager.h"
#include "../Texture/Texture.hpp"
#include "../Material/Material.hpp"
#include "../Lights/Lights.hpp"
#include <string>

using namespace std;

RenderPass::RenderPass(nlohmann::json pass)
{
    ShaderManager* sm = ShaderManager::GetInstance();
    auto shaders = pass["shader"];
    m_program = sm->RequestProgram(shaders["vert"],shaders["frag"]);

    auto texArrayJs = pass["textures"];
    for(int i = 0; i < texArrayJs.size(); ++i)
    {
        auto texJs = texArrayJs[i];
        auto texture = Texture(texJs["file"]);
        m_textures.push_back(TextureShaderParam
        {
            glGetUniformLocation(m_program,((string)texJs["key"]).c_str()) ,
            texture
        });
    }
    auto matJs = pass["material"];
    Material material = Material(matJs["file"]);

    auto floats = pass["float"];
    for(int i = 0; i < floats.size(); ++i)
    {
        auto f = floats[i];
        if(f["key"] == "shininess")
        {
            m_uniformf.push_back(Uniformf{
                    glGetUniformLocation(m_program,((string)f["key"]).c_str()),
                    f["key"],
                    material.GetShininess()
            });
        }
        else{
            m_uniformf.push_back(Uniformf{
                    glGetUniformLocation(m_program,((string)f["key"]).c_str()),
                    f["key"],
                    f["value"]
            });
        }
    }

    auto vec3s = pass["vec3"];
    for(int i = 0; i < vec3s.size(); ++i)
    {
        auto v = vec3s[i];
        if(v["key"] == "ka")
        {
            m_uniform3fv.push_back(Uniform3fv{
                    glGetUniformLocation(m_program,((string)v["key"]).c_str()),
                    v["key"],
                    material.GetAmbient()
            });
        }
        else if(v["key"] == "kd")
        {
            m_uniform3fv.push_back(Uniform3fv{
                    glGetUniformLocation(m_program,((string)v["key"]).c_str()),
                    v["key"],
                    material.GetDiffuse()
            });
        }
        else if(v["key"] == "ks")
        {
            m_uniform3fv.push_back(Uniform3fv{
                    glGetUniformLocation(m_program,((string)v["key"]).c_str()),
                    v["key"],
                    material.GetSpecular()
            });
        }
        else{
            auto vec = v["value"];
            m_uniform3fv.push_back(Uniform3fv{
                    glGetUniformLocation(m_program,((string)v["key"]).c_str()),
                    v["key"],
                    glm::vec3(vec["x"],vec["y"],vec["z"])
            });
        }
    }

    auto vec4s = pass["vec4"];
    for(int i = 0; i < vec4s.size(); ++i)
    {
        auto v = vec4s[i];
        if(v["key"] == "ia")
        {
            m_uniform4fv.push_back(Uniform4fv{
                    glGetUniformLocation(m_program,((string)v["key"]).c_str()),
                    v["key"],
                    glm::vec4(ia,1.f)
            });
        }
        else{
            auto vec = v["value"];
            m_uniform4fv.push_back(Uniform4fv{
                    glGetUniformLocation(m_program,((string)v["key"]).c_str()),
                    v["key"],
                    glm::vec4(vec["x"],vec["y"],vec["z"],vec["w"])
            });
        }
    }

    if(pass["cull"] == "front")
    {
        m_cullFace = GL_FRONT;
    }
    else if(pass["cull"] == "back")
    {
        m_cullFace = GL_BACK;
    }
}