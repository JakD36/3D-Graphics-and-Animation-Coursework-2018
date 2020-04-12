//
//  Scene1.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Scene1.hpp"
#include "../Utils/ProfileService.h"
#include <glm/gtx/quaternion.hpp>
#include "../Shaders/ShaderManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../GameObject/GameObject.hpp"

using namespace std;

Scene1::Scene1() noexcept{
    int profiler = ProfilerService::GetInstance()->StartTimer("Scene Initialisation");
    double startTime = glfwGetTime(); // So we can see how long it takes for all models to load

    ShaderManager* shaderManager = ShaderManager::GetInstance();
    GLuint baseProgram = shaderManager->RequestProgram("Shaders/vs.glsl","Shaders/fs.glsl");

    m_torch = new GameObject("Set/newTorch.obj","Materials/newTorch.mtl","Textures/newTorchCol.ktx",baseProgram);
    m_torch->m_position = m_playerPosition + glm::quat(glm::vec3(glm::radians(m_pitchOffset),glm::radians(m_yawOffset),0.0f)) * glm::vec3(0.0f,0.0f,m_sphereRadius);//Utils::Spherical2Cartesian(m_sphereRadius,m_yawOffset,-m_pitchOffset);
    m_objs.push_back(m_torch);

    // Front of room
    m_objs.push_back(new GameObject("Set/front.obj", "Materials/front.mtl", "Textures/front.ktx", baseProgram));
    
    // Back wall
    GameObject* go = new GameObject("Set/back.obj","Materials/back.mtl","Textures/back.ktx",baseProgram);
    go->m_rotation.y = 180.f;
    go->m_position = glm::vec3(0.0f,2.0f,3.0f);
    m_objs.push_back(go);
    
    // Roof
    go = new GameObject("Set/roof.obj","Materials/roof.mtl","Textures/roof.ktx",baseProgram);
    go->m_position.y = 2.5f;
    m_objs.push_back(go);
    
    // Beams
    go = new GameObject("Set/beam.obj","Materials/beam.mtl","Textures/beam.ktx",baseProgram);
    go->m_position = glm::vec3(0.0f,2.61f,0.0f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    go = new GameObject("Set/beam.obj","Materials/beam.mtl","Textures/beam.ktx",baseProgram);
    go->m_position = glm::vec3(0.0f,2.61f,-1.5f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    go = new GameObject("Set/beam.obj","Materials/beam.mtl","Textures/beam.ktx",baseProgram);
    go->m_position = glm::vec3(0.0f,2.61f,1.5f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Planks
    // Plank 1
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(2.2f,1.5f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,5.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 2
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(2.f,1.3f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,1.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 3
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.65f,1.6f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,2.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 4
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.4f,1.5f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,-5.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 5
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.1f,1.3f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,1.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 6
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(0.8f,1.55f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,-12.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 7
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(0.5f,1.55f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,-1.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 8
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(0.1f,1.55f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,6.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 9
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(0.6f,1.7f,-2.85f);
    go->m_rotation = glm::vec3(90.0f,0.0f,80.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 10
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.f,1.15f,-2.85f);
    go->m_rotation = glm::vec3(90.0f,0.0f,110.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 11
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.8f,1.65f,-2.85f);
    go->m_rotation = glm::vec3(90.0f,0.0f,60.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 12
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.4f,1.85f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,85.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 13
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(-1.4f,1.55f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,95.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 14
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(-1.4f,1.2f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,90.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 15
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(-1.4f,0.85f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,80.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 16
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(1.4f,0.5f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,100.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Plank 17
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",baseProgram);
    go->m_position = glm::vec3(-1.4f,0.2f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,95.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Floor
    m_objs.push_back(new GameObject("Set/floor.obj", "Materials/floor.mtl", "Textures/floor.ktx", baseProgram));
    
    // Wall
    // Wall 1
    go = new GameObject("Set/wall.obj","Materials/wall.mtl","Textures/wall.ktx",baseProgram);
    go->m_position = glm::vec3(3.0f,1.25f,0.f);
    go->m_rotation = glm::vec3(0.0f,180.0f,0.f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    // Wall 2
    go = new GameObject("Set/wall.obj","Materials/wall.mtl","Textures/wall.ktx",baseProgram);
    go->m_position = glm::vec3(-3.0f,1.25f,0.f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_objs.push_back(go);
    
    //Lightbulb
    GLuint lightProgram = shaderManager->RequestProgram("Shaders/vs_light.glsl","Shaders/fs_light.glsl");
    m_bulb = new GameObject("Set/bulb.obj","Materials/bulb.mtl","Textures/bulb.ktx",lightProgram);
    m_objs.push_back(m_bulb);
    
    // Wire
    m_wire = new GameObject("Set/wire.obj","Materials/wire.mtl","Textures/wire.ktx",baseProgram);
    m_objs.push_back(m_wire);
    
    // Table 
    go = new GameObject("Set/table.obj","Materials/table.mtl","Textures/table.ktx",baseProgram);
    go->m_position = glm::vec3(1.8f,1.0f,1.8f);
    go->m_rotation.y = 45.f;
    m_objs.push_back(go);

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

