//
//  sceneGraph.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef sceneGraph_hpp
#define sceneGraph_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <gli/gli.hpp>

#include <stdio.h>
#include "modelObject.h"
#include "modelObjectSingle.h"
#include "modelObjectInst.h"
#include "camera.hpp"
#include <vector>

class sceneGraph{
protected:
    // Other variables!
    lightStruct lights[LIGHTSN];// Creates our array of lightStructs to store details on all the lights in the scene.
    vector<modelObject*> Objs;  // This is a vector of pointers to the objects in the scene, this allows us to render everything in the scene by adding to this vector of objects no matter if its a modelObject single or instanced.
    camera sceneCamera;
    
    // Do we have objects that are global to the game
    
public:
    sceneGraph();
    
    // Other methods
    virtual void update(double currentTime) = 0;
    
    vector<modelObject*> getObjs();
    camera getCamera();
    
    
    glm::vec3 posOnSphere(float radius,float yaw,float pitch);
    void printVec3(glm::vec3 vec3,string str1,string str2,string str3);
    lightStruct* getLights();
    
    /* Actions Performed!
     These are the actions that can be performed in the game
     For example, jump, move forward/backward, turn, alter direction looking at, switch light on or off.
    */
    virtual void usePrimary() = 0;
    virtual void useSecondary() = 0;
    virtual void turnCamera(double xoffset, double yoffset);
    
};


#endif /* sceneGraph_hpp */
