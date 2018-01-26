//
//  render.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 27/10/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"

void GLapp::render(double currentTime) {
    
    // So now to render to the framebuffer texture instead of screen
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,framebufferTexture,0);

    glm::vec4 black = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
    glViewport(0, 0, windowWidth, windowHeight); // Convert all our projected coordinates to screen coordinates for the texture
    glClearBufferfv(GL_COLOR, 0, &black[0]);
    static const GLfloat one = 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    
    // To create our camera, we use the lookAt function generate the viewMatrix
    // It takes 3 inputs, the position of the camera, the point in space it is facing and which direction is up, so its orientated properly
    glm::mat4 viewMatrix = glm::lookAt(cameraPos,                       // eye
                                       cameraPos+cameraFront,           // centre, we need to use the pos+cameraFront to make sure its pointing to the right point in space
                                       glm::vec3(0.0f, 1.0f, 0.0f));    // up
    
    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    for(int n = 0;n<Objs.size();n++){
        Objs[n]->setupRender(proj_matrix,lights,cameraPos);
        Objs[n]->render(proj_matrix,viewMatrix,lights,cameraPos);
    }
    
    // SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(-windowWidth*2, -windowHeight*2, windowWidth*4, windowHeight*4);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); //not needed as we are just displaying a single quad
    glUseProgram(displayProgram);
    glBindVertexArray(displayVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
