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
#include "../Texture/Texture.hpp"
#include "../Views/Camera.hpp"
#include "../Transform.h"
#include "../Views/RenderTaskManager.h"

using namespace std;

// TODO: need to treat Render passes like shaders as these values are shared across every gameobjec that uses it
// TODO: Handle errors in the json parsing and report the mistake to allow for adding values without worrying about one mistake crashing application

GameObject::GameObject(const GameObject &go) noexcept : m_mesh(go.m_mesh)
{
    m_transform = new Transform(go.m_transform);
    m_renderTask = go.m_renderTask;
}

GameObject::GameObject(string renderPass, string meshMethadata, Transform* parent) noexcept : m_mesh(meshMethadata){
    PROFILE(profiler,"GO Init");

    m_transform = new Transform(parent);
    m_renderTask = RenderTaskManager::GetInstance()->RequestRenderTask(renderPass);

    ENDPROFILE(profiler);
}

void GameObject::Render(Camera camera) noexcept{
    PROFILE(profiler,"GO Render");

    glm::mat4 m = m_transform->BuildModelMatrix();
    glm::mat4 mv = camera.BuildViewMat() * m;
    glm::mat4 mvp = camera.ProjectionMatrix() * mv;

    for(int i = 0; i < m_renderTask->m_passes.size(); ++i)
    {
        RenderPass& pass = m_renderTask->m_passes[i];
        glUseProgram(pass.m_program);

        glBindVertexArray(m_mesh.GetVao());

        glUniformMatrix4fv(glGetUniformLocation(pass.m_program,"modelMatrix"), 1, GL_FALSE, &m[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(pass.m_program,"mv"), 1, GL_FALSE, &mv[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(pass.m_program,"mvp"), 1, GL_FALSE, &mvp[0][0]);

        glUniform3fv(glGetUniformLocation(pass.m_program,"viewPosition"),1,&camera.GetPosition()[0]); // The camera position

        for(int j = 0; j < pass.m_textures.size(); ++j)
        {
            glActiveTexture(GL_TEXTURE0+j);
            glBindTexture(GL_TEXTURE_2D,pass.m_textures[j].m_texture);
            glUniform1i(pass.m_textures[j].m_location, j);
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

        glCullFace(pass.m_cullFace);
        glEnable(GL_CULL_FACE);

        glDrawArrays(GL_TRIANGLES, 0, m_mesh.GetVertCount());
    }

    ENDPROFILE(profiler);
}
