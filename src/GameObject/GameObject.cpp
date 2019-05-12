//
//  GameObject.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "GameObject.hpp"


GameObject::GameObject(Mesh* mesh, Material* mat, Texture* tex, ShaderPipeline* pipeline){
    m_mesh = mesh;
    m_material = mat;
    m_texture = tex;
    
    m_shaderPipeline = pipeline;
}

GameObject::GameObject(string meshPath, string materialPath, string texturePath, ShaderPipeline* pipeline){
    m_mesh = ResourceService<Mesh>::GetInstance()->Request(meshPath);
    m_material = ResourceService<Material>::GetInstance()->Request(materialPath);
    m_texture = ResourceService<Texture>::GetInstance()->Request(texturePath);

    m_shaderPipeline = pipeline;
}

void GameObject::Render(glm::mat4& proj_matrix, glm::mat4& viewMatrix, lightStruct lights[], glm::vec3& camera){
    // For each model Object
    glUseProgram(m_shaderPipeline->m_program);
    glBindVertexArray(m_mesh->m_vao);
    
    // Pass projection matrix through to the shaders through the uniforms
    glUniformMatrix4fv(glGetUniformLocation(m_shaderPipeline->m_program,"proj_matrix"), 1, GL_FALSE, &proj_matrix[0][0]);
    // Bind textures and samplers - using 0 as I know there is only one texture - need to extend.
    
    // Assign the values to each of the appropriate uniforms so that they can be accessed by the shaders
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->m_texture[0]);
    
    // Pass a number of values through to the shaders through the uniforms
    glUniform1i(glGetUniformLocation(m_shaderPipeline->m_program,"tex"), 0);                    // The texture
    glUniform4f(glGetUniformLocation(m_shaderPipeline->m_program,"viewPosition"),camera.x,camera.y,camera.z,1.0f); // The camera position
    glUniform4f(glGetUniformLocation(m_shaderPipeline->m_program, "ia"), lightStruct::ia.r, lightStruct::ia.g, lightStruct::ia.b, 1.0f); // The ambient light intensity, as there is only one for the scene
    glUniform3f(glGetUniformLocation(m_shaderPipeline->m_program, "ka"), m_material->m_ka.r,m_material->m_ka.g,m_material->m_ka.b); // The material materials ambient reflectivity constant
    glUniform3f(glGetUniformLocation(m_shaderPipeline->m_program, "kd"), m_material->m_kd.r,m_material->m_kd.g,m_material->m_kd.b); // The material materials diffused reflectivity constant
    glUniform3f(glGetUniformLocation(m_shaderPipeline->m_program, "ks"), m_material->m_ks.r,m_material->m_ks.g,m_material->m_ks.b); // The material materials specular reflectivity constant
    glUniform1f(glGetUniformLocation(m_shaderPipeline->m_program, "shininess"), m_material->m_shininess); // The materials shininess indices
    glUniform1f(glGetUniformLocation(m_shaderPipeline->m_program,"lightConstant"),0.25f);       // Constant used for attenuation, taken from lecture notes
    glUniform1f(glGetUniformLocation(m_shaderPipeline->m_program,"lightLinear"),0.7f);          // Constant used for attenuation, taken from lecture notes
    glUniform1f(glGetUniformLocation(m_shaderPipeline->m_program,"lightQuadratic"),1.0f);       // Constant used for attenuation, taken from lecture notes
    
    
    // Loop through each of the lights and provide the necessary information to the shader through the uniforms
    for(int n = 0;n<LIGHTSN;n++){
        /*
         Need to pass each piece of information in seperately, so that the shaders can read it
         The name of each element is constructed as follows
         lights[#].KEY
         where the # is the number of that light
         and the KEY is the information wanted for that light, such as on, type, lightPosition
         */
        glUniform1i(glGetUniformLocation(m_shaderPipeline->m_program,("lights["+to_string(n)+"].on").c_str()),lights[n].lightOn);
        glUniform1i(glGetUniformLocation(m_shaderPipeline->m_program,("lights["+to_string(n)+"].type").c_str()),lights[n].type);
        glUniform4f(glGetUniformLocation(m_shaderPipeline->m_program,
                                         ("lights["+to_string(n)+"].lightPosition").c_str()),
                    lights[n].position.x,lights[n].position.y,lights[n].position.z,1.0f);
        
        glUniform4f(glGetUniformLocation(m_shaderPipeline->m_program,
                                         ("lights["+to_string(n)+"].direction").c_str()),
                    lights[n].direction.x,lights[n].direction.y,lights[n].direction.z,0.0f);
        glUniform4f(glGetUniformLocation(m_shaderPipeline->m_program,("lights["+to_string(n)+"].id").c_str()),lights[n].id.r,lights[n].id.g,lights[n].id.b,1.0f);
        glUniform1f(glGetUniformLocation(m_shaderPipeline->m_program, ("lights["+to_string(n)+"].lightSpotCutOff").c_str()), glm::cos(glm::radians(15.0f)));
        glUniform1f(glGetUniformLocation(m_shaderPipeline->m_program, ("lights["+to_string(n)+"].lightSpotOuterCutOff").c_str()), glm::cos(glm::radians(20.0f)));
        
        glUniform4f(glGetUniformLocation(m_shaderPipeline->m_program,("lights["+to_string(n)+"].is").c_str()),lights[n].is.r,lights[n].is.g,lights[n].is.b,1.0f);
    }
    
    /*
     This is the same for all model Objects, so this is contained within the modelObject abstract class,
     To render the object, call this method followed by the render method that is implemented in subclasses.
     */
    
    // Apply each of the transformations to a 4x4 identity matrix
    
    // Order of rotations is incredibly important and was discovered through trial and error
    // Concatenate matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_position); // mat4(1.0f) generates a 4x4 identity matrix (same as x1) to start the transforms
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, m_scale);
    
    // Once the final model matrix has been calculated pass to the shaders through the uniforms to do the final calculations
    glUniformMatrix4fv(glGetUniformLocation(m_shaderPipeline->m_program,"modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderPipeline->m_program,"viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, m_mesh->m_vertices.size()); // Draw vertices, need to tell it how many vertices to draw so third argument is the out.vertices.size.
    
}
