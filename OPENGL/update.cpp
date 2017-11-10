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
        objectPos.y-=0.05f;
    }
    if(keyStatus[GLFW_KEY_W] == true){
        objectPos.y+=0.05f;
    }
    if(keyStatus[GLFW_KEY_A] == true){
        objectPos.x-=0.05f;
    }
    if(keyStatus[GLFW_KEY_D] == true){
        objectPos.x+=0.05f;
    }
    if(keyStatus[GLFW_KEY_LEFT] == true){
        objectRot.y+=1.0f;
    }
    if(keyStatus[GLFW_KEY_RIGHT] == true){
        objectRot.y-=1.0f;
        cout<<objectRot.y<<endl;
    }
    if(keyStatus[GLFW_KEY_UP] == true){
        objectRot.x+=0.05f;
    }
    if(keyStatus[GLFW_KEY_DOWN] == true){
        objectRot.x-=0.05f;
    }
    if(keyStatus[GLFW_KEY_I] == true){
        objectPos.z-=0.05f;
    }
    if(keyStatus[GLFW_KEY_K] == true){
        objectPos.z+=0.05f;
    }
    if(keyStatus[GLFW_KEY_Q] == true){
        objectScale.x -= 0.05f; objectScale.y -= 0.05f; objectScale.z-=0.05f;
    }
    if(keyStatus[GLFW_KEY_E] == true){
        objectScale.x += 0.05f; objectScale.y += 0.05f; objectScale.z += 0.05f;
    }
    if(keyStatus[GLFW_KEY_1] == true){
        cameraPos.x += 0.05f;
    }
    if(keyStatus[GLFW_KEY_2] == true){
        cameraPos.x -= 0.05f;
    }
    if(keyStatus[GLFW_KEY_3] == true){
        cameraPos.y += 0.5f;
    }
    if(keyStatus[GLFW_KEY_4] == true){
        cameraPos.y -= 0.5f;
    }
    
}
