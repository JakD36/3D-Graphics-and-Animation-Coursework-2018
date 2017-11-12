//
//  modelObjectSingle.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "modelObjectSingle.h"

void modelObjectSingle::render(glm::mat4& proj_matrix,glm::mat4& viewMatrix) const{
    // For each model Object
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, &proj_matrix[0][0]);
    // Bind textures and samplers - using 0 as I know there is only one texture - need to extend.
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glUniform1i(tex_location, 0);
    
    // Concatenate matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    glm::mat4 mv_matrix = viewMatrix * modelMatrix;
    
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &mv_matrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, out_vertices.size());
    
}
