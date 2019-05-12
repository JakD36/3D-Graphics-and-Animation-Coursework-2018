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
#include <vector>

#include "../ModelObjects/modelObject.h"
#include "../ModelObjects/modelObjectSingle.h"
#include "../ModelObjects/modelObjectInst.h"


#include "../GameObject/GameObject.hpp"
#include "../Utils/VectorUtils.hpp"


/* Abstract class for each scene to be based on
 
 Each scene should
 Contain the objects and lights for the scene
 The player
 and methods to access the details of these for the Renderer
*/
class SceneGraph{
protected:
    
    lightStruct m_lights[LIGHTSN];// Creates our array of lightStructs to store details on all the lights in the scene.
    vector<GameObject*> m_Objs;  // This is a vector of pointers to the objects in the scene, this allows us to render everything in the scene by adding to this vector of objects no matter if its a modelObject single or instanced.
    
    // Do we have objects that are global to the game
    glm::vec3 m_playerPosition;
public:
    SceneGraph();
    virtual ~SceneGraph();
    
    // Other methods
    virtual void Update(double currentTime) = 0; // Function to update the scene, every frame based on keyframing or procedural animation
    
    vector<GameObject*> GetObjs(); // Return the vector of pointers to all the objects in the scene
    
    lightStruct* GetLights();
    glm::vec3 GetPlayerPosition();
    
    /* Actions Performed!
     These are the actions that can be performed in the game
     For example, jump, move forward/backward, turn, alter direction looking at, switch light on or off.
    */
    virtual void UsePrimary() = 0;
    virtual void UseSecondary() = 0;
    virtual void Turn(GLfloat yaw, GLfloat pitch) = 0;
};


#endif /* sceneGraph_hpp */
