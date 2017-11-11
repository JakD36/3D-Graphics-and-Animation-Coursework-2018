//
//  update.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

void GLapp::update(double currentTime) {
    if(keyStatus[GLFW_KEY_S] == true){
        torchObj.position.y-=0.05f;
    }
    if(keyStatus[GLFW_KEY_W] == true){
        torchObj.position.y+=0.05f;
    }
    if(keyStatus[GLFW_KEY_A] == true){
        torchObj.position.x-=0.05f;
    }
    if(keyStatus[GLFW_KEY_D] == true){
        torchObj.position.x+=0.05f;
    }
    if(keyStatus[GLFW_KEY_LEFT] == true){
        torchObj.rotation+=1.0f;
    }
    if(keyStatus[GLFW_KEY_RIGHT] == true){
        torchObj.rotation.y-=1.0f;
        cout<<torchObj.rotation.y<<endl;
    }
    if(keyStatus[GLFW_KEY_UP] == true){
        torchObj.rotation.x+=0.05f;
    }
    if(keyStatus[GLFW_KEY_DOWN] == true){
        torchObj.rotation.x-=0.05f;
    }
    if(keyStatus[GLFW_KEY_I] == true){
        torchObj.position.z-=0.05f;
    }
    if(keyStatus[GLFW_KEY_K] == true){
        torchObj.position.z+=0.05f;
    }
    if(keyStatus[GLFW_KEY_Q] == true){
        torchObj.scale.x -= 0.05f; torchObj.scale.y -= 0.05f; torchObj.scale.z-=0.05f;
    }
    if(keyStatus[GLFW_KEY_E] == true){
        torchObj.scale.x += 0.05f; torchObj.scale.y += 0.05f; torchObj.scale.z += 0.05f;
    }
    if(keyStatus[GLFW_KEY_1] == true){
        cameraPos.x += 0.05f;
    }
    if(keyStatus[GLFW_KEY_2] == true){
        cameraPos.x -= 0.05f;
    }
    if(keyStatus[GLFW_KEY_3] == true){
        cameraPos.z += 0.5f;
    }
    if(keyStatus[GLFW_KEY_4] == true){
        cameraPos.z -= 0.5f;
    }
    
}
