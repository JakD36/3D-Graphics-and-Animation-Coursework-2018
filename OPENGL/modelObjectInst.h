//
//  modelObjectInst.h
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#ifndef modelObjectInst_h
#define modelObjectInst_h

#include "modelObject.h"
#include <vector>

class modelObjectInst: public modelObject{ // This is how you publically inherit from another class
public:
    // We have two sub classes of model Object, inst ie instanced and single.
    // the instanced object requires a vector to store all the positions, rotations and scale information for each instance of that object
    // To do this a vector of vec3 is used so we can have dont have to specify the number of items that can be in the scene.
    
    // Every object in the scene could be of the type modelObjectInst
    // however there is an increased overhead storing evertying as vectors when you only need one of that object
    vector<glm::vec3> position;
    vector<glm::vec3> rotation;
    vector<glm::vec3> scale;
    
    virtual void render(glm::mat4&,glm::mat4&, lightStruct[], glm::vec3&) const; // Our pure virtual function for modelObjectInst
    
    // To speed up the process of creating new objects, an add method where the values default to the centre of the scene
    void add(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
             glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f),
             glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f));
};


#endif /* modelObjectInst_h */
