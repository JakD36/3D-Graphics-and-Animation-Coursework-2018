//
//  modelObjectInst.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "modelObjectInst.h"

void modelObjectInst::add(glm::vec3 position,glm::vec3 rotation,glm::vec3 scale){ // Add the values of the new object to the end of each vector
    this->position.push_back(position);
    this->rotation.push_back(rotation);
    this->scale.push_back(scale);
}

void modelObjectInst::render(glm::mat4& proj_matrix,glm::mat4& viewMatrix, lightStruct lights[],glm::vec3& camera) const{
    // This differs slightly from the code to render a single model object as it requires going through each instance in a for loop
    for(int i = 0;i<position.size();i++) {        
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f),position[i]);    // Initiate the model matrix as a 4x4 identity matrix
        
        // Apply our rotation transformations, in the order z,y,x. Order is incredibly important and this working was found through trial and error
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation[i].z), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation[i].x), glm::vec3(1.0f, 0.0f, 0.0f));
        
        // Apply scale transformation
        modelMatrix = glm::scale(modelMatrix,scale[i]);
        
        glUniformMatrix4fv(glGetUniformLocation(program,"modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]); 
        glUniformMatrix4fv(glGetUniformLocation(program,"viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, out_vertices.size()); // Draw the vertices
    }
    

}
