//
//  update.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

void GLapp::update(double currentTime) {
    double dt = currentTime - prevTime;
    prevTime = currentTime;
    
    // Swinging light
    double ay = (-9.81/lightRadius)*cos(glm::radians(lightPitch));
    lightPitch += v*dt + 0.5 * ay * pow(dt,2);
    v += ay*dt;
    
    if(lightPitch>0){
        lightPitch = 0;
        v = 0;
    }else if(lightPitch<-180){
        lightPitch = -180;
        v = 0;
    }
    lights[0].position = glm::vec3(0.0f,2.25f,0.0f) + posOnSphere(lightRadius, lightYaw, lightPitch);
    bulb.position = lights[0].position;
    bulb.rotation.x = -lightPitch-90;
    
    if(LMBClicked == true){
        if(lights[2].lightOn){
            lights[2].lightOn = false;
        }
        else{
            lights[2].lightOn = true;
        }
        LMBClicked = false;
    }
    
    
    lights[2].position = cameraPos+cameraFront/3.0f;
}
