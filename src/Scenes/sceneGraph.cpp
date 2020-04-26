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
#include "../Utils/ProfilerService.h"
#include "../Views/Camera.hpp"
#include <json.hpp>
#include <fstream>
#include <cstdio>
#include "../Shaders/ShaderManager.h"

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

std::array<LightData,k_lightCount> SceneGraph::GetLights() noexcept{
    return m_lights;
}

glm::vec3 SceneGraph::GetPlayerPosition() noexcept{
    return m_playerPosition;
}

Camera* SceneGraph::GetCamera() noexcept
{
    return p_camera;
}

void SceneGraph::Deserialise(std::string filepath)
{
    nlohmann::json js;
    fstream file(filepath);
    if(file.is_open())
    {
        ShaderManager* shaderManager = ShaderManager::GetInstance();
        file >> js;
        int objectCount = js["objects"].size();
        for(int i = 0; i < objectCount; ++i)
        {
            nlohmann::json object = js["objects"][i];
            GLuint program = shaderManager->RequestProgram(object["vert"],object["frag"]);

            GameObject* go = new GameObject(object["mesh"],object["material"],object["texture"],program);

            nlohmann::json position = object["position"];
            go->m_position = glm::vec3(position["x"],position["y"],position["z"]);

            nlohmann::json rotation = object["rotation"];
            go->m_rotation = glm::vec3(rotation["x"],rotation["y"],rotation["z"]);

            nlohmann::json scale = object["scale"];
            go->m_scale = glm::vec3(scale["x"],scale["y"],scale["z"]);

            m_objs.push_back(go);
        }
    }
    else
    {
        printf("Error: file %s could not be opened.\n",filepath.c_str());
    }
}