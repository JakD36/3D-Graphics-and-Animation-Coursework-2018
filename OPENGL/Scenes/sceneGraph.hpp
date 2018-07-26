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
#include <vector>


/* Abstract class for each scene to be based on
 
 Each scene should
 Contain the objects and lights for the scene
 The player
 and methods to access the details of these for the renderer
*/
class sceneGraph{
protected:
    
    lightStruct lights[LIGHTSN];// Creates our array of lightStructs to store details on all the lights in the scene.
    vector<modelObject*> Objs;  // This is a vector of pointers to the objects in the scene, this allows us to render everything in the scene by adding to this vector of objects no matter if its a modelObject single or instanced.
    
    // Do we have objects that are global to the game
    glm::vec3 playerPosition;
public:
    sceneGraph();
    ~sceneGraph();
    
    // Other methods
    virtual void update(double currentTime) = 0; // Function to update the scene, every frame based on keyframing or procedural animation
    
    vector<modelObject*> getObjs(); // Return the vector of pointers to all the objects in the scene
    
    
    glm::vec3 posOnSphere(float radius,float yaw,float pitch);
    void printVec3(glm::vec3 vec3,string str1,string str2,string str3);
    lightStruct* getLights();
    glm::vec3 getPlayerPosition();
    
    /* Actions Performed!
     These are the actions that can be performed in the game
     For example, jump, move forward/backward, turn, alter direction looking at, switch light on or off.
    */
    virtual void usePrimary() = 0;
    virtual void useSecondary() = 0;
    virtual void turn(GLfloat yaw, GLfloat pitch) = 0;
    
    
};


#endif /* sceneGraph_hpp */
