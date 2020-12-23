//
//  GameObject.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "GameObject.hpp"
#include "../Profiling/ProfilerService.h"
#include "../Rendering/Lights/Lights.hpp"
#include "../Rendering/Texture/Texture.hpp"
#include "../Rendering/Views/Camera.hpp"
#include "Transform.h"

using namespace std;

// TODO: need to treat Render passes like shaders as these values are shared across every gameobjec that uses it
// TODO: Handle errors in the json parsing and report the mistake to allow for adding values without worrying about one mistake crashing application

GameObject::GameObject(const GameObject &go) noexcept : m_mesh(go.m_mesh), m_renderTask(go.m_renderTask)
{
    m_transform = new Transform(go.m_transform);
}

GameObject::GameObject(string renderPass, string meshMethadata, Transform* parent) noexcept : m_mesh(meshMethadata), m_renderTask(renderPass){
    PROFILE(profiler,"GO Init");

    m_transform = new Transform(parent);

    ENDPROFILE(profiler);
}

GameObject::~GameObject()
{
//    delete m_transform; // TODO: Fix memory leak in transform hierarchy
}

void GameObject::Render(Camera camera) noexcept{
    PROFILE(profiler,"Render " + m_renderTask.GetName());

    glm::mat4 m = m_transform->BuildModelMatrix();
    glm::mat4 mv = camera.BuildViewMat() * m;
    glm::mat4 mvp = camera.ProjectionMatrix() * mv;

    m_mesh.Bind();

    for(int i = 0; i < m_renderTask.size(); ++i)
    {
        RenderPass& pass = m_renderTask[i];
        pass.Bind();

        pass.SetMatrix4x4("modelMatrix",m);
        pass.SetMatrix4x4("mv",mv);
        pass.SetMatrix4x4("mvp",mvp);

        pass.SetCameraPosition(camera.GetPosition());

        m_mesh.Draw();
    }

    ENDPROFILE(profiler);
}
