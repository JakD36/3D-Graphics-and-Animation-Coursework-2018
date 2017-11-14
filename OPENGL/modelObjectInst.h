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
};


#endif /* modelObjectInst_h */
