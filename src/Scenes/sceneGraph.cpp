//
//  sceneGraph.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "SceneGraph.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Utils/VectorUtils.hpp"
#include "../Utils/ProfileService.h"
#include "../Views/Camera.hpp"

using namespace std;

SceneGraph::SceneGraph() noexcept{
    m_playerPosition = glm::vec3(0.0f,1.6f,0.0f);
    p_camera = new Camera();
}

SceneGraph::~SceneGraph() noexcept{
    for(int n = 0; n < m_objs.size(); n++){
        delete m_objs[n];
        m_objs[n] = NULL;
    }
}

vector<GameObject*> SceneGraph::GetObjs() noexcept{
    return m_objs;
}

LightData* SceneGraph::GetLights() noexcept{
    return m_lights;
}

glm::vec3 SceneGraph::GetPlayerPosition() noexcept{
    return m_playerPosition;
}

Camera* SceneGraph::GetCamera() noexcept
{
    return p_camera;
}