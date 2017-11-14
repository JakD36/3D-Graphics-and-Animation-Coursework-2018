//
//  modelObjectSingle.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 11/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "modelObjectSingle.h"

void modelObjectSingle::render(glm::mat4& proj_matrix,glm::mat4& viewMatrix, lightStruct lights[],glm::vec3& camera) const{
    // For each model Object
    glUseProgram(program);
    glBindVertexArray(vao);
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, &proj_matrix[0][0]);
    // Bind textures and samplers - using 0 as I know there is only one texture - need to extend.
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glUniform1i(tex_location, 0);
    
    glUniform4f(glGetUniformLocation(program,"viewPosition"),camera.x,camera.y,camera.z,1.0f);
    glUniform4f(glGetUniformLocation(program, "ia"), lightStruct::ia.r, lightStruct::ia.g, lightStruct::ia.b, 1.0f);
    glUniform1f(glGetUniformLocation(program, "ka"), ka);
    glUniform1f(glGetUniformLocation(program, "kd"), kd);
    glUniform1f(glGetUniformLocation(program, "ks"), ks);
    glUniform1f(glGetUniformLocation(program, "shininess"), shininess);
    glUniform1f(glGetUniformLocation(program,"lightConstant"),0.25f);
    glUniform1f(glGetUniformLocation(program,"lightLinear"),0.7f);
    glUniform1f(glGetUniformLocation(program,"lightQuadratic"),1.0f);
    
    for(int n = 0;n<3;n++){
        glUniform1i(glGetUniformLocation(program,("lights["+to_string(n)+"].type").c_str()),lights[n].type);
        glUniform4f(glGetUniformLocation(program,
                                         ("lights["+to_string(n)+"].lightPosition").c_str()),
                    lights[n].position.x,lights[n].position.y,lights[n].position.z,1.0f);
        
        glUniform4f(glGetUniformLocation(program,
                                         ("lights["+to_string(n)+"].direction").c_str()),
                    lights[n].direction.x,lights[n].direction.y,lights[n].direction.z,0.0f);
        glUniform4f(glGetUniformLocation(program,("lights["+to_string(n)+"].id").c_str()),lights[n].id.r,lights[n].id.g,lights[n].id.b,1.0f);
        glUniform1f(glGetUniformLocation(program, ("lights["+to_string(n)+"].lightSpotCutOff").c_str()), glm::cos(glm::radians(15.0f)));
        glUniform1f(glGetUniformLocation(program, ("lights["+to_string(n)+"].lightSpotOuterCutOff").c_str()), glm::cos(glm::radians(20.0f)));
        
        glUniform4f(glGetUniformLocation(program,("lights["+to_string(n)+"].is").c_str()),lights[n].is.r,lights[n].is.g,lights[n].is.b,1.0f);
    }
//    glUniform4f(glGetUniformLocation(program,
//                                     "lights.lightPosition"),
//                lights[0].position.x,lights[0].position.y,lights[0].position.z,1.0f);
//    glUniform4f(glGetUniformLocation(program,"lights.id"),1.0f,1.0f,1.0f,1.0f);
//    glUniform4f(glGetUniformLocation(program,"lights.is"),lights[0].is.r,lights[0].is.g,lights[0].is.b,1.0f);
    
    
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
