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
#include "../Profiling/ProfilerService.h"
#include "../Views/Camera.hpp"
#include <json.hpp>
#include <fstream>
#include <cstdio>
#include "../Shaders/ShaderManager.h"
#include "../Transform.h"
#include <sys/stat.h>

using namespace std;

SceneGraph::SceneGraph() noexcept{
    m_playerTransform = new Transform();
    m_playerTransform->m_localPosition = glm::vec3(0.0f,1.6f,0.0f);
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
    return m_playerTransform->m_localPosition;
}

Camera* SceneGraph::GetCamera() noexcept
{
    return p_camera;
}

void SceneGraph::Update(double deltaTime) noexcept
{
    UpdateFile();
}

void SceneGraph::UpdateFile() noexcept
{
    struct stat buf;
    stat(m_fileInfo.path.c_str(),&buf);

    if(m_fileInfo.lastModified != buf.st_mtime)
    {
        printf("Reloading Scene!\n");
        m_fileInfo.lastModified = buf.st_mtime;
        m_objs.clear();
        m_objectKeys.clear();

        m_lightKeys.clear();
        m_lights.fill(LightData());
        Deserialise(m_fileInfo.path);
        UpdateHandles();
    }
}

void SceneGraph::Deserialise(std::string filepath)
{
    nlohmann::json js;
    fstream file(filepath);

    assert(file.is_open());

    file >> js;
    int objectCount = js["objects"].size();
    int initialCount = m_objs.size();
    if(m_objs.capacity() < objectCount + initialCount) // Error missing copy constructor or default constructor?
    {
        m_objs.reserve(initialCount + objectCount);
        m_objectKeys.reserve(initialCount + objectCount);
    }

    for(int i = 0; i < objectCount; ++i)
    {
        nlohmann::json object = js["objects"][i];

        m_objectKeys.push_back(object["key"]);

        m_objs.push_back(GameObject(object["render"],object["mesh"]));

        nlohmann::json position = object["position"];
        m_objs[initialCount+i].m_transform->m_localPosition = glm::vec3(position["x"],position["y"],position["z"]);

        nlohmann::json rotation = object["rotation"];
        m_objs[initialCount+i].m_transform->m_localRotation = glm::quat(glm::vec3(glm::radians((float)rotation["x"]),glm::radians((float)rotation["y"]),glm::radians((float)rotation["z"])));

        nlohmann::json scale = object["scale"];
        m_objs[initialCount+i].m_transform->m_localScale = glm::vec3(scale["x"],scale["y"],scale["z"]);
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