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

    ShaderManager* shaderManager = ShaderManager::GetInstance();
    GLuint baseProgram = shaderManager->RequestProgram("Shaders/vs.glsl","Shaders/fs.glsl");

    // Dynamic objects

    m_torch = new GameObject("Set/newTorch.obj","Materials/newTorch.mtl","Textures/newTorchCol.ktx",baseProgram);
    m_torch->m_position = m_playerPosition + glm::quat(glm::vec3(glm::radians(m_pitchOffset),glm::radians(m_yawOffset),0.0f)) * glm::vec3(0.0f,0.0f,m_sphereRadius);
    m_objs.push_back(m_torch);

    //Lightbulb
    GLuint lightProgram = shaderManager->RequestProgram("Shaders/vs_light.glsl","Shaders/fs_light.glsl");
    m_bulb = new GameObject("Set/bulb.obj","Materials/bulb.mtl","Textures/bulb.ktx",lightProgram);
    m_objs.push_back(m_bulb);
    
    // Wire
    m_wire = new GameObject("Set/wire.obj","Materials/wire.mtl","Textures/wire.ktx",baseProgram);
    m_objs.push_back(m_wire);

    // Lamp
    GameObject* lamp = new GameObject("Set/lamp.obj","Materials/lamp.mtl","Textures/lamp.ktx",baseProgram);
    lamp->m_position = glm::vec3(2.4f,1.025f,1.6f);
    lamp->m_rotation.y = 120.f;
    m_objs.push_back(lamp);
    
    // Add lights to scene, number of lights determined by const int k_lightCount
    // The ceiling light
    m_lights[0].type = LightType::point; // So we have an enum for point and spot lights that lets us know which light we are dealing with
    m_lights[0].position = glm::vec3(0.0f,2.0f,0.0f);
    m_lights[0].id = glm::vec3(5.0f,5.0f,5.0f);
    m_lights[0].is = glm::vec3(5.0f,5.0f,5.0f);
    
    // red light by the door
    m_lights[1].type = LightType::point;
    m_lights[1].position = glm::vec3(-1.7f,1.5f,-2.8f);
    m_lights[1].id = glm::vec3(1.5f,0.0f,0.0f);
    m_lights[1].is = glm::vec3(0.5f,0.0f,0.0f);
    
    // torch light
    m_lights[2].type = LightType::spot;
    m_lights[2].position = glm::vec3(0.0f,1.0f,0.0f);
    m_lights[2].direction = glm::vec3(0.0f,0.0f,1.0f); // its facing the same direction of the player
    m_lights[2].id = glm::vec3(7.0f,7.0f,7.0f);
    m_lights[2].is = glm::vec3(5.0f,5.0f,5.0f);
    
    // the lamp light
    m_lights[3].type = LightType::spot;
    m_lights[3].position = lamp->m_position + glm::vec3(0.0f,0.5f,0.0f);
    m_lights[3].direction = glm::vec3(-0.5f,-0.3f,0.3f);
    m_lights[3].id = glm::vec3(5.0f,5.0f,5.0f);
    m_lights[3].is = glm::vec3(1.0f,1.0f,1.0f);

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
    m_lights[0].position = glm::vec3(0.0f,2.49f,0.0f) + glm::quat(glm::vec3(glm::radians(m_lightPitch),glm::radians(m_lightYaw),0.0f)) * glm::vec3(0.0f,0.0f,m_lightRadius);
    m_bulb->m_position = m_lights[0].position;
    m_bulb->m_rotation.x = -m_lightPitch-90;
    
    m_wire->m_position = glm::vec3(0.0f,2.49f,0.0f) + glm::quat(glm::vec3(glm::radians(m_lightPitch),glm::radians(m_lightYaw),0.0f)) * glm::vec3(0.0f,0.0f,0.125f); // need to set the wires position and rotation to match the bulb
    m_wire->m_rotation.x = -m_lightPitch-90;
    
    m_lights[2].position = m_playerPosition+glm::vec3(0.0f,0.0f,1.0f)/3.0f; // we can update the position of the torch light based on the direction of the camera

    ProfilerService::GetInstance()->StopTimer(profiler);
}

Scene1::~Scene1() noexcept {}

void Scene1::UsePrimary() noexcept{
    if(m_lights[2].lightOn){
        m_lights[2].lightOn = false;
    }
    else{
        m_lights[2].lightOn = true;
    }
}

void Scene1::UseSecondary() noexcept{
    if(m_lights[0].lightOn){
        m_lights[0].lightOn = false;
    }
    else{
        m_lights[0].lightOn = true;
    }
}

void Scene1::Turn(GLfloat yaw, GLfloat pitch) noexcept{
    m_torch->m_position = m_playerPosition + glm::quat(glm::vec3(glm::radians(pitch+m_pitchOffset),glm::radians(yaw+m_yawOffset),0.0f)) * glm::vec3(0.0f,0.0f,m_sphereRadius);

    m_torch->m_rotation.x = pitch;
    m_torch->m_rotation.y = yaw;
    m_lights[2].direction = glm::quat(glm::vec3(glm::radians(pitch),glm::radians(yaw),0.0f)) * glm::vec3(0.0f,0.0f,1.0f);
}

