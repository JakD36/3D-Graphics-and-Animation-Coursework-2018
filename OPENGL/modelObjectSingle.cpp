//
//  modelObjectSingle.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "modelObjectSingle.h"

void modelObjectSingle::render(glm::mat4& proj_matrix,glm::mat4& viewMatrix, lightStruct lights[],glm::vec3& camera) const{
        
    // Concatenate matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    glm::mat4 mv_matrix = viewMatrix * modelMatrix;
    
    glUniformMatrix4fv(glGetUniformLocation(program,"modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(program,"viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, out_vertices.size());
    
}