//
//  update.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

void GLapp::update(double currentTime) {
    double dt = currentTime - prevTime; // get the change in time between the last frame and the current frame so to accurately calculate any movement
    prevTime = currentTime;
    
    // Swinging light
    double ay = (-9.81/lightRadius)*cos(glm::radians(lightPitch)); // this is the equation for the acceleration acting upon the light
    lightPitch += v*dt + 0.5 * ay * pow(dt,2); // this is the equation for angular motion
    v += ay*dt; // and the new velocity on the pendulum
    
    if(lightPitch>-20){ // we need to cap the height the pendulum reaches, otherwise inaccuracies will cause the pendulum to keep swinging higher and higher
        lightPitch = -20; // by capping the swing between -20 and -160 so that the swing is more natural, could do 0 and -180 but prefer the cone look
//        v = 0; // at the peak of its swing the pendulum has zero velocity and max acceleration. whereas at the bottom of its swing it has zero acceleration and a max velocity
    }else if(lightPitch<-160){
        lightPitch = -160;
//        v = 0;
    }
    lights[0].position = glm::vec3(0.0f,2.25f,0.0f) + posOnSphere(lightRadius, lightYaw, lightPitch); // here we set the position of light source
    bulb.position = lights[0].position; // set the position of the bulb to match
    bulb.rotation.x = -lightPitch-90;   // set the rotation of the bulb to match the angles for the model are weird, so dont ask why its so messed up
                                        // trial and error was used to find the right combination
    
    wire.position = glm::vec3(0.0f,2.25f,0.0f) + posOnSphere(0.125, lightYaw, lightPitch); // need to set the wires position and rotation to match the bulb
    wire.rotation.x = -lightPitch-90;
    
    if(LMBClicked){ // check the bool set in one of the callbacks to see if the left mouse button was clicked if so we switch off the torch
        if(lights[2].lightOn){ // we need to check if the light is on or off first, if its on we need to switch it off and vice versa
            lights[2].lightOn = false;
        }
        else{
            lights[2].lightOn = true;
        }
        LMBClicked = false;
    }else if(RMBClicked){ // same as above but different light
        if(lights[0].lightOn){
            lights[0].lightOn = false;
        }
        else{
            lights[0].lightOn = true;
        }
        RMBClicked = false;
    }

    lights[2].position = cameraPos+cameraFront/3.0f; // we can update the position of the torch light based on the direction of the camera 
}
