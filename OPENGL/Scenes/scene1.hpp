//
//  scene1.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef scene1_hpp
#define scene1_hpp

#include "sceneGraph.hpp"
#include "camera.hpp"


/*
 The first scene of this project,
 by inheriting from the sceneGraph abstract can have multiple scenes in the project and swap the scenes out by instantiating an object of the
 new scene and providing a pointer to the scene to the renderer object.
*/
class scene1: public sceneGraph{
private:
    
    // Objects in this scene, using pointers that are global for this object in case they are to be used in both initialisation and update through each frame.
    modelObjectSingle*       torchObj;
    modelObjectSingle*       front;
    modelObjectInst*         planks;
    modelObjectSingle*       floor;
    modelObjectInst*         wall;
    modelObjectSingle*       back;
    modelObjectSingle*       roof;
    modelObjectInst*         beam;
    modelObjectSingle*       bulb;
    modelObjectSingle*       wire;
    modelObjectSingle*       table;
    modelObjectSingle*       lamp;
    
    // These are the details for the swinging light above the player, it is a pendulum
    float lightRadius = 0.25f;          // The radius at which the light swings
    float lightYaw = 0.0f;              // instantiate its yaw and give its initial yaw as 0
    float lightPitch = -20.0f;          // instantiate its pitch and give its initial pitch of -20 so that it can start with a 0 velocity and still move
    double          v = 0;              // instantiate the lights velocity and start it with 0, this way it starts moving as gravity starts pulling it down
    
    double prevTime = 0;       // time at the previous frame
    
    
    // This specifically is for the torch, attached to the player.
    float sphereRadius = 0.4;                           // Its sitting 0.4 m away from the camera
    float yawOffset = 30;                               // Its offset from the camera by the 30 degrees in the yaw
    float pitchOffset = 20;                             // Its offset from the camera by the 20 degrees in the pitch

public:
    scene1();
    
    
    
    virtual void update(double currentTime); // Update the scene every frame
    
    // Actions to be performed, same as the rest of the game
    virtual void usePrimary();
    virtual void useSecondary();
    virtual void turn(GLfloat yaw, GLfloat pitch);
};
#endif /* scene1_hpp */
