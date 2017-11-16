//
//  update.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

void GLapp::update(double currentTime) {
    
    lights[2].position = cameraPos+cameraFront;
}
