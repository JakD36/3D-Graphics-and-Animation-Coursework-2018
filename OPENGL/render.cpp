//
//  render.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

void GLapp::render(double currentTime) {
    static const GLfloat silver[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    
    glViewport(0, 0, windowWidth*2, windowHeight*2); // PICTURE WAS RESTRICTED TO BOTTOM LEFT CORNER, MULTIPLYING BY 2 SEEMED TO FIX THE ISSUE BUT I HAVE NO IDEA WHAT WENT WRONG
    glClearBufferfv(GL_COLOR, 0, silver);
    static const GLfloat one = 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glm::mat4 viewMatrix = glm::lookAt(cameraPos, // eye
                                       cameraPos+cameraFront, // centre
                                       glm::vec3(0.0f, 1.0f, 0.0f));// up

    // Render each object
    for(int n = 0;n<Objs.size();n++){
        Objs[n]->render(proj_matrix,viewMatrix,light,cameraPos);
    }
}
