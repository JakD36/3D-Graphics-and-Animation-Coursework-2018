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
}

vector<GameObject>& SceneGraph::GetObjs() noexcept{
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
        int initialCount = m_objs.size();
//        if(m_objs.capacity() < objectCount + initialCount) // Error missing copy constructor or default constructor?
//        {
//            m_objs.resize(initialCount + objectCount);
//            m_objectKeys.resize(initialCount + objectCount);
//        }

        for(int i = 0; i < objectCount; ++i)
        {
            nlohmann::json object = js["objects"][i];

            m_objectKeys.push_back(object["key"]);

            GLuint program = shaderManager->RequestProgram(object["vert"],object["frag"]);
            m_objs.push_back(GameObject(object["mesh"],object["material"],object["texture"],program));

            nlohmann::json position = object["position"];
            m_objs[initialCount+i].m_position = glm::vec3(position["x"],position["y"],position["z"]);

            nlohmann::json rotation = object["rotation"];
            m_objs[initialCount+i].m_rotation = glm::vec3(rotation["x"],rotation["y"],rotation["z"]);

            nlohmann::json scale = object["scale"];
            m_objs[initialCount+i].m_scale = glm::vec3(scale["x"],scale["y"],scale["z"]);
            string str = "Key: %s\n"
                         "Mesh: %s\n"
                         "material: %s\n"
                         "texture: %s\n\n";
            printf(str.c_str(),((string)object["key"]).c_str(),((string)object["mesh"]).c_str(),((string)object["material"]).c_str(),((string)object["texture"]).c_str());
        }

        int lightCount = js["lights"].size();
        for(int i = 0; i < lightCount && k_lightCount; ++i)
        {
            nlohmann::json light = js["lights"][i];
            m_lightKeys.push_back(light["key"]);

            m_lights[i].type = light["type"]; // So we have an enum for point and spot lights that lets us know which light we are dealing with

            if(m_lights[i].type == LightType::spot)
            {
                nlohmann::json direction = light["direction"];
                m_lights[i].direction = glm::vec3(direction["x"],direction["y"],direction["z"]);
            }

            nlohmann::json position = light["position"];
            m_lights[i].position = glm::vec3(position["x"],position["y"],position["z"]);

            nlohmann::json id = light["id"];
            m_lights[i].id = glm::vec3(id["r"],id["g"],id["b"]);

            nlohmann::json is = light["is"];
            m_lights[i].is = glm::vec3(is["r"],is["g"],is["b"]);
        }
    }
    else
    {
        printf("Error: file %s could not be opened.\n",filepath.c_str());
    }
    printf("Finished Scene Deserialisation.\n%d Objects read in\n%d lights read in\n",m_objs.size(),m_lights.size());
}