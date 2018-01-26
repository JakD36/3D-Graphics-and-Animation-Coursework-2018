//
//  modelObjectSingle.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "modelObjectSingle.h"

void modelObjectSingle::render(glm::mat4& proj_matrix,glm::mat4& viewMatrix, lightStruct lights[],glm::vec3& camera) const{
    
    // Apply each of the transformations to a 4x4 identity matrix
    
    // Order of rotations is incredibly important and was discovered through trial and error
    // Concatenate matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position); // mat4(1.0f) generates a 4x4 identity matrix (same as x1) to start the transforms
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, scale);
    
    // Once the final model matrix has been calculated pass to the shaders to do the final calculations
    glUniformMatrix4fv(glGetUniformLocation(program,"modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(program,"viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, out_vertices.size()); // Draw vertices
    
}
