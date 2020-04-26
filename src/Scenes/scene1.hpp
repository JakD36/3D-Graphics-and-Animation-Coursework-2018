//
//  Scene1.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef Scene1_hpp
#define Scene1_hpp

#include "SceneGraph.hpp"
#include <GL/glew.h>

class GameObject;

class Scene1: public SceneGraph{
private:
    int m_bulb, m_wire, m_torch, m_torchLight, m_bulbLight;
    
    // Swinging light
    float m_lightRadius = 0.25f;
    float m_lightYaw = 0.0f;
    float m_lightPitch = -20.0f;
    double m_v = 0; // Light Velocity

    // This specifically is for the torch, attached to the player.
    float m_sphereRadius = 0.4;
    float m_yawOffset = 30;
    float m_pitchOffset = 20;
public:
    Scene1() noexcept;
    virtual ~Scene1() noexcept;
    virtual void Update(double deltaTime) noexcept;

    virtual void UsePrimary() noexcept;
    virtual void UseSecondary() noexcept;
    virtual void Turn(GLfloat yaw, GLfloat pitch) noexcept;
};
#endif /* Scene1_hpp */
