//
//  Scene1.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "Scene1.hpp"

#include "../Views/Render.hpp"

Scene1::Scene1(){
    // Initialise Objects
    // Instantiate Object
    // initModel
    // initTexture
    // loadMat
    // sort any other variables that need set
    double startTime = glfwGetTime(); // So we can see how long it takes for all models to load

    ShaderPipeline* pipeline = new ShaderPipeline("Shaders/vs.glsl","Shaders/fs.glsl");

    m_torch = new GameObject("Set/newTorch.obj","Materials/newTorch.mtl","Textures/newTorchCol.ktx",pipeline);
    m_torch->m_position = m_playerPosition + Utils::Spherical2Cartesian(m_sphereRadius,m_yawOffset,-m_pitchOffset);
    m_Objs.push_back(m_torch);
    
    // Set
    // Room
    
    // Front of room
    m_Objs.push_back(new GameObject("Set/front.obj","Materials/front.mtl","Textures/front.ktx",pipeline));
    
    // Back wall
    GameObject* go = new GameObject("Set/back.obj","Materials/back.mtl","Textures/back.ktx",pipeline);
    go->m_rotation.y = 180.f;
    go->m_position = glm::vec3(0.0f,2.0f,3.0f);
    m_Objs.push_back(go);
    
    // Roof
    go = new GameObject("Set/roof.obj","Materials/roof.mtl","Textures/roof.ktx",pipeline);
    go->m_position.y = 2.5f;
    m_Objs.push_back(go);
    
    // Beams
    go = new GameObject("Set/beam.obj","Materials/beam.mtl","Textures/beam.ktx",pipeline);
    go->m_position = glm::vec3(0.0f,2.61f,0.0f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    go = new GameObject("Set/beam.obj","Materials/beam.mtl","Textures/beam.ktx",pipeline);
    go->m_position = glm::vec3(0.0f,2.61f,-1.5f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    go = new GameObject("Set/beam.obj","Materials/beam.mtl","Textures/beam.ktx",pipeline);
    go->m_position = glm::vec3(0.0f,2.61f,1.5f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Planks
    // Plank 1
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(2.2f,1.5f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,5.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 2
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(2.f,1.3f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,1.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 3
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.65f,1.6f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,2.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 4
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.4f,1.5f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,-5.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 5
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.1f,1.3f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,1.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 6
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(0.8f,1.55f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,-12.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 7
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(0.5f,1.55f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,-1.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 8
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(0.1f,1.55f,-3.f);
    go->m_rotation = glm::vec3(90.0f,0.0f,6.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 9
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(0.6f,1.7f,-2.85f);
    go->m_rotation = glm::vec3(90.0f,0.0f,80.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 10
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.f,1.15f,-2.85f);
    go->m_rotation = glm::vec3(90.0f,0.0f,110.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 11
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.8f,1.65f,-2.85f);
    go->m_rotation = glm::vec3(90.0f,0.0f,60.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 12
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.4f,1.85f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,85.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 13
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(-1.4f,1.55f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,95.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 14
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(-1.4f,1.2f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,90.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 15
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(-1.4f,0.85f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,80.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 16
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(1.4f,0.5f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,100.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Plank 17
    go = new GameObject("Set/plank.obj","Materials/plank.mtl","Textures/plank.ktx",pipeline);
    go->m_position = glm::vec3(-1.4f,0.2f,-3.2f);
    go->m_rotation = glm::vec3(90.0f,0.0f,95.0f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Floor
    m_Objs.push_back(new GameObject("Set/floor.obj","Materials/floor.mtl","Textures/floor.ktx",pipeline));
    
    // Wall
    // Wall 1
    go = new GameObject("Set/wall.obj","Materials/wall.mtl","Textures/wall.ktx",pipeline);
    go->m_position = glm::vec3(3.0f,1.25f,0.f);
    go->m_rotation = glm::vec3(0.0f,180.0f,0.f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    // Wall 2
    go = new GameObject("Set/wall.obj","Materials/wall.mtl","Textures/wall.ktx",pipeline);
    go->m_position = glm::vec3(-3.0f,1.25f,0.f);
    go->m_rotation = glm::vec3(0.0f,0.0f,0.f);
    go->m_scale = glm::vec3(1.f,1.f,1.f);
    m_Objs.push_back(go);
    
    //Lightbulb
    ShaderPipeline* lightPipeline = new ShaderPipeline("Shaders/vs_light.glsl","Shaders/fs_light.glsl");
    m_bulb = new GameObject("Set/bulb.obj","Materials/bulb.mtl","Textures/bulb.ktx",lightPipeline);
    m_Objs.push_back(m_bulb);
    
    // Wire
    m_wire = new GameObject("Set/wire.obj","Materials/wire.mtl","Textures/wire.ktx",pipeline);
    m_Objs.push_back(m_wire);
    
    // Table 
    go = new GameObject("Set/table.obj","Materials/table.mtl","Textures/table.ktx",pipeline);
    go->m_position = glm::vec3(1.8f,1.0f,1.8f);
    go->m_rotation.y = 45.f;
    m_Objs.push_back(go);

    // Lamp
    GameObject* lamp = new GameObject("Set/lamp.obj","Materials/lamp.mtl","Textures/lamp.ktx",pipeline);
    lamp->m_position = glm::vec3(2.4f,1.025f,1.6f);
    lamp->m_rotation.y = 120.f;
    m_Objs.push_back(lamp);
    
    // Add lights to scene, number of lights determined by const int LIGHTSN
    // The ceiling light
    m_lights[0].type = lightType::point; // So we have an enum for point and spot lights that lets us know which light we are dealing with
    m_lights[0].position = glm::vec3(0.0f,2.0f,0.0f);
    m_lights[0].id = glm::vec3(5.0f,5.0f,5.0f);
    m_lights[0].is = glm::vec3(5.0f,5.0f,5.0f);
    
    // red light by the door
    m_lights[1].type = lightType::point;
    m_lights[1].position = glm::vec3(-1.7f,1.5f,-2.8f);
    m_lights[1].id = glm::vec3(1.5f,0.0f,0.0f);
    m_lights[1].is = glm::vec3(0.5f,0.0f,0.0f);
    
    // torch light
    m_lights[2].type = lightType::spot;
    m_lights[2].position = glm::vec3(0.0f,1.0f,0.0f);
    m_lights[2].direction = glm::vec3(0.0f,0.0f,1.0f); // its facing the same direction of the player
    m_lights[2].id = glm::vec3(7.0f,7.0f,7.0f);
    m_lights[2].is = glm::vec3(5.0f,5.0f,5.0f);
    
    // the lamp light
    m_lights[3].type = lightType::spot;
    m_lights[3].position = lamp->m_position +glm::vec3(0.0f,0.5f,0.0f);
    m_lights[3].direction = glm::vec3(-0.5f,-0.3f,0.3f);
    m_lights[3].id = glm::vec3(5.0f,5.0f,5.0f);
    m_lights[3].is = glm::vec3(1.0f,1.0f,1.0f);
    
    
    
    cout<<"Time to load "<<glfwGetTime()-startTime<<endl;   // Just a nice thing to know
    RenderManager rm;
    for(vector<GameObject*>::iterator iter = m_Objs.begin(); iter != m_Objs.end(); ++iter)
    {
        rm.QueueToAddOrUpdate(*iter);
    }
    rm.Batch();
}



void Scene1::Update(double currentTime){
    double dt = currentTime - m_prevTime; // get the change in time between the last frame and the current frame so to accurately calculate any movement
    m_prevTime = currentTime;
    
    // Swinging light
    double ay = (-9.81/m_lightRadius)*cos(glm::radians(m_lightPitch)); // this is the equation for the acceleration acting upon the light
    m_lightPitch += m_v*dt + 0.5 * ay * pow(dt,2); // this is the equation for angular motion
    m_v += ay*dt; // and the new velocity on the pendulum
    
    if(m_lightPitch>-20){ // we need to cap the height the pendulum reaches, otherwise inaccuracies will cause the pendulum to keep swinging higher and higher
        m_lightPitch = -20; // by capping the swing between -20 and -160 so that the swing is more natural, could do 0 and -180 but prefer the cone look
                          //        v = 0; // at the peak of its swing the pendulum has zero velocity and max acceleration. whereas at the bottom of its swing it has zero acceleration and a max velocity
    }else if(m_lightPitch<-160){
        m_lightPitch = -160;
        //        v = 0;
    }
    m_lights[0].position = glm::vec3(0.0f,2.49f,0.0f) + Utils::Spherical2Cartesian(m_lightRadius, m_lightYaw, m_lightPitch); // here we set the position of light source
    m_bulb->m_position = m_lights[0].position; // set the position of the bulb to match
    m_bulb->m_rotation.x = -m_lightPitch-90;   // set the rotation of the bulb to match the angles for the model are weird, so dont ask why its so messed up
                                         // trial and error was used to find the right combination
    
    m_wire->m_position = glm::vec3(0.0f,2.49f,0.0f) + Utils::Spherical2Cartesian(0.125, m_lightYaw, m_lightPitch); // need to set the wires position and rotation to match the bulb
    m_wire->m_rotation.x = -m_lightPitch-90;
    
    
    m_lights[2].position = m_playerPosition+glm::vec3(0.0f,0.0f,1.0f)/3.0f; // we can update the position of the torch light based on the direction of the camera
}

// Activates the primary action, this case turning the torch on or off
void Scene1::UsePrimary(){
    if(m_lights[2].lightOn){ // we need to check if the light is on or off first, if its on we need to switch it off and vice versa
        m_lights[2].lightOn = false;
    }
    else{
        m_lights[2].lightOn = true;
    }
}

// Activates the secondary action, this case turning the ceiling light on or off
void Scene1::UseSecondary(){
    if(m_lights[0].lightOn){
        m_lights[0].lightOn = false;
    }
    else{
        m_lights[0].lightOn = true;
    }
}


// Turns the player to face the direction specified by the spherical coordinates
void Scene1::Turn(GLfloat yaw, GLfloat pitch){

    m_torch->m_position = m_playerPosition + Utils::Spherical2Cartesian(1, yaw+m_yawOffset, pitch-m_pitchOffset) * m_sphereRadius; // our torchs position is based off the camera position
    // try adding vectors instead of adding yaw and pitch

    m_torch->m_rotation.x = -pitch;       // Torch seems to be backwards in its model so has to have its pitch rotated the other way
    m_torch->m_rotation.y = yaw;
    m_lights[2].direction = Utils::Spherical2Cartesian(1, yaw, pitch); // the light from the torch just goes where we are looking
}

