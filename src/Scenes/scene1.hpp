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
#include "../Views/Camera.hpp"
#include "../ResourceManager/ResourceService.hpp"
#include "../Utils/Profile.h"

/*
 The first scene of this project,
 by inheriting from the sceneGraph abstract can have multiple scenes in the project and swap the scenes out by instantiating an object of the
 new scene and providing a pointer to the scene to the Renderer object.
*/
class Scene1: public SceneGraph{
private:
    
    // Objects in this scene, using pointers that are global for this object in case they are to be used in both initialisation and update through each frame.
    GameObject *m_bulb, *m_wire, *m_torch;
    
    // These are the details for the swinging light above the player, it is a pendulum
    float m_lightRadius = 0.25f;          // The radius at which the light swings
    float m_lightYaw = 0.0f;              // instantiate its yaw and give its initial yaw as 0
    float m_lightPitch = -20.0f;          // instantiate its pitch and give its initial pitch of -20 so that it can start with a 0 velocity and still move
    double          m_v = 0;              // instantiate the lights velocity and start it with 0, this way it starts moving as gravity starts pulling it down
    
    double m_prevTime = 0;       // time at the previous frame
    
    
    // This specifically is for the torch, attached to the player.
    float m_sphereRadius = 0.4;                           // Its sitting 0.4 m away from the camera
    float m_yawOffset = 30;                               // Its offset from the camera by the 30 degrees in the yaw
    float m_pitchOffset = 20;                             // Its offset from the camera by the 20 degrees in the pitch

public:
    Scene1();
    virtual void Update(double currentTime); // Update the scene every frame
    
    // Actions to be performed, same as the rest of the game
    virtual void UsePrimary();
    virtual void UseSecondary();
    virtual void Turn(GLfloat yaw, GLfloat pitch);
};
#endif /* Scene1_hpp */
