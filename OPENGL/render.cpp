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
    
    // For each model Object
    glUseProgram(torchObj.program);
    glBindVertexArray(torchObj.vao);
    glUniformMatrix4fv(torchObj.proj_location, 1, GL_FALSE, &proj_matrix[0][0]);
    // Bind textures and samplers - using 0 as I know there is only one texture - need to extend.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, torchObj.texture[0]);
    glUniform1i(torchObj.tex_location, 0);

    // Concatenate matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), objectPos);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, objectScale);
    glm::mat4 mv_matrix = viewMatrix * modelMatrix;
    
    glUniformMatrix4fv(torchObj.mv_location, 1, GL_FALSE, &mv_matrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, torchObj.out_vertices.size());

//    glUseProgram(pac.program);
//    glBindVertexArray(pac.vao);
//    glUniformMatrix4fv(pac.proj_location, 1, GL_FALSE, &proj_matrix[0][0]);
//    // Two lines handle rotation and displacement
////        glm::mat4 modelMatrix2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,15.0f));
////        modelMatrix2 = glm::rotate(modelMatrix2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
////        glm::mat4 mv_matrix2 = viewMatrix * modelMatrix2;
////    glUniformMatrix4fv(pac.mv_location, 1, GL_FALSE, &mv_matrix2[0][0]);
////    glDrawArrays(GL_TRIANGLES, 0, pac.out_vertices.size());
//
//    float aPosX[6] = {0.0f, 0.0f, 20.0f, -20.0f, 0.0f, 0.0f};
//    float aPosZ[6] = {20.f, -20.0f, 0.0f, 0.0f,0.0f, 0.0f};
//    float aPosY[6] = {0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 20.0f};
//    for(int i= 0;i< 6;i++) {
//         glm::mat4 modelMatrix2 = glm::translate(glm::mat4(1.0f),
//         glm::vec3(aPosX[i],aPosY[i], aPosZ[i]));
//         //mv_matrix2 = glm::rotate(mv_matrix, rotY, glm::vec3(1.0f,
//         //0.0f, 0.0f));
//         //mv_matrix = glm::rotate(mv_matrix, rotX, glm::vec3(0.0f, 1.0f,
//         //0.0f));
//         glm::mat4 mv_matrix2 = viewMatrix * modelMatrix2;
//         glUniformMatrix4fv(pac.mv_location, 1, GL_FALSE, &mv_matrix2[0][0]);
//         glDrawArrays(GL_TRIANGLES, 0, pac.out_vertices.size());
//    }
}
