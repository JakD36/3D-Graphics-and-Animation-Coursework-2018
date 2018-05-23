//
//  modelObjectSingle.h
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#ifndef modelObjectSingle_h
#define modelObjectSingle_h

#include "modelObject.h"

class modelObjectSingle: public modelObject{
public:
    // A single model object only requires its own position, rotation and scale
    glm::vec3 position  = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 rotation  = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 scale     = glm::vec3(1.0f,1.0f,1.0f);

    virtual void render(glm::mat4&,glm::mat4&,lightStruct[],glm::vec3&) const; // pure virtual function 
};

#endif /* modelObjectSingle_h */
