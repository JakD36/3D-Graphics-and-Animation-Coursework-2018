//
//  Scene1.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Scene1.hpp"
#include "../Utils/ProfilerService.h"
#include <glm/gtx/quaternion.hpp>
#include "../Shaders/ShaderManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../GameObject/GameObject.hpp"

using namespace std;

Scene1::Scene1() noexcept{
    int profiler = ProfilerService::GetInstance()->StartTimer("Scene Initialisation");
    double startTime = glfwGetTime(); // So we can see how long it takes for all models to load
    
    Deserialise("Set/room.json");

    // Dynamic objects
    int lampHandle = -1, lampLightHandle = -1;
    for(int i = 0, count = m_objectKeys.size(); i < count; ++i)
    {
        if(m_objectKeys[i] == "torch")
            m_torch = i;
        else if(m_objectKeys[i] == "bulb")
            m_bulb = i;
        else if(m_objectKeys[i] == "wire")
            m_wire = i;
        else if(m_objectKeys[i] == "lamp")
            lampHandle = i;
    }

    for(int i = 0, count = m_lightKeys.size(); i < count; ++i)
    {
        if(m_lightKeys[i] == "ceiling")
            m_bulbLight = i;
        else if(m_lightKeys[i] == "torch")
            m_torchLight = i;
        else if(m_lightKeys[i] == "lamp")
            lampLightHandle = i;
    }

    m_objs[m_torch].m_position = m_playerPosition + glm::quat(glm::vec3(glm::radians(m_pitchOffset),glm::radians(m_yawOffset),0.0f)) * glm::vec3(0.0f,0.0f,m_sphereRadius);

    m_lights[lampLightHandle].position = m_objs[lampHandle].m_position + glm::vec3(0.0f,0.5f,0.0f);

    cout<<"Time to load "<<glfwGetTime()-startTime<<endl;   // Just a nice thing to know

    ProfilerService::GetInstance()->StopTimer(profiler);
}

void Scene1::Update(double deltaTime) noexcept{
    int profiler = ProfilerService::GetInstance()->StartTimer("Scene Update");
    
    // Swinging light
    double ay = (-9.81/m_lightRadius)*cos(glm::radians(m_lightPitch)); // this is the equation for the acceleration acting upon the light
    m_lightPitch += m_v * deltaTime + 0.5 * ay * pow(deltaTime, 2); // this is the equation for angular motion
    m_v += ay * deltaTime;
    
    if(m_lightPitch>-20){
        m_lightPitch = -20;

    }else if(m_lightPitch<-160){
        m_lightPitch = -160;
    }
    m_lights[m_bulbLight].position = glm::vec3(0.0f,2.49f,0.0f) + glm::quat(glm::vec3(glm::radians(m_lightPitch),glm::radians(m_lightYaw),0.0f)) * glm::vec3(0.0f,0.0f,m_lightRadius);
    m_objs[m_bulb].m_position = m_lights[m_bulbLight].position;
    m_objs[m_bulb].m_rotation.x = -m_lightPitch-90;

    m_objs[m_wire].m_position = glm::vec3(0.0f,2.49f,0.0f) + glm::quat(glm::vec3(glm::radians(m_lightPitch),glm::radians(m_lightYaw),0.0f)) * glm::vec3(0.0f,0.0f,0.125f); // need to set the wires position and rotation to match the bulb
    m_objs[m_wire].m_rotation.x = -m_lightPitch-90;
    
    m_lights[m_torchLight].position = m_playerPosition+glm::vec3(0.0f,0.0f,1.0f)/3.0f; // we can update the position of the torch light based on the direction of the camera

    ProfilerService::GetInstance()->StopTimer(profiler);
}

Scene1::~Scene1() noexcept {}

void Scene1::UsePrimary() noexcept{
    if(m_lights[m_torchLight].lightOn){
        m_lights[m_torchLight].lightOn = false;
    }
    else{
        m_lights[m_torchLight].lightOn = true;
    }
}

void Scene1::UseSecondary() noexcept{
    if(m_lights[m_bulbLight].lightOn){
        m_lights[m_bulbLight].lightOn = false;
    }
    else{
        m_lights[m_bulbLight].lightOn = true;
    }
}

void Scene1::Turn(GLfloat yaw, GLfloat pitch) noexcept{
    m_objs[m_torch].m_position = m_playerPosition + glm::quat(glm::vec3(glm::radians(pitch+m_pitchOffset),glm::radians(yaw+m_yawOffset),0.0f)) * glm::vec3(0.0f,0.0f,m_sphereRadius);

    m_objs[m_torch].m_rotation.x = pitch;
    m_objs[m_torch].m_rotation.y = yaw;
    m_lights[m_torchLight].direction = glm::quat(glm::vec3(glm::radians(pitch),glm::radians(yaw),0.0f)) * glm::vec3(0.0f,0.0f,1.0f);
}

