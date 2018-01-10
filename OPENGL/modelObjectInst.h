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

class modelObjectInst: public modelObject{
public:
    vector<glm::vec3> position;
    vector<glm::vec3> rotation;
    vector<glm::vec3> scale;
    
    virtual void render(glm::mat4&,glm::mat4&, lightStruct[], glm::vec3&) const;
    void add(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
             glm::vec3 rotation = glm::vec3(0.0f,0.0f,0.0f),
             glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f));
};


#endif /* modelObjectInst_h */
