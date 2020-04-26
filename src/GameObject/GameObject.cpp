//
//  GameObject.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "GameObject.hpp"
#include "../Utils/ProfilerService.h"
#include "../Lights/Lights.hpp"
#include "../ResourceManager/ResourceService.hpp"
#include <glm/gtx/transform.hpp>
#include "../Mesh/Mesh.hpp"
#include "../Material/Material.hpp"
#include "../Texture/Texture.hpp"
#include "../Views/Camera.hpp"

using namespace std;

GameObject::GameObject(Mesh* mesh, Material* mat, Texture* tex, GLuint shaderProgram) noexcept{
    m_mesh = mesh;
    m_material = mat;
    m_texture = tex;
    
    m_program = shaderProgram;
}

GameObject::GameObject(string meshPath, string materialPath, string texturePath, GLuint shaderProgram) noexcept{
    int profiler = ProfilerService::GetInstance()->StartTimer("GO Init");

    m_mesh = ResourceService<Mesh>::GetInstance()->Request(meshPath);
    m_material = ResourceService<Material>::GetInstance()->Request(materialPath);
    m_texture = ResourceService<Texture>::GetInstance()->Request(texturePath);

    m_program = shaderProgram;

    ProfilerService::GetInstance()->StopTimer(profiler);
}



void GameObject::Render(Camera camera) noexcept{
    int profiler = ProfilerService::GetInstance()->StartTimer("GO Render");

    // For each model Object
    glUseProgram(m_program);
    glBindVertexArray(m_mesh->m_vao);

    // Bind textures and samplers - using 0 as I know there is only one texture - need to extend.
    // Assign the values to each of the appropriate uniforms so that they can be accessed by the shaders

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture->m_texture[0]);

    glUniform1i(glGetUniformLocation(m_program,"tex"), 0);                    // The texture

    // Pass a number of values through to the shaders through the uniforms

    glUniform3fv(glGetUniformLocation(m_program,"viewPosition"),1,&camera.GetPosition()[0]); // The camera position
    glUniform4fv(glGetUniformLocation(m_program, "ia"),1, &glm::vec4(ia,1.f)[0]); // The ambient light intensity, as there is only one for the scene
    glUniform3fv(glGetUniformLocation(m_program, "ka"),1, &m_material->m_ka[0]); // The material materials ambient reflectivity constant
    glUniform3fv(glGetUniformLocation(m_program, "kd"),1, &m_material->m_kd[0]); // The material materials diffused reflectivity constant
    glUniform3fv(glGetUniformLocation(m_program, "ks"),1, &m_material->m_ks[0]); // The material materials specular reflectivity constant
    glUniform1f(glGetUniformLocation(m_program, "shininess"), m_material->m_shininess); // The materials shininess indices
    glUniform1f(glGetUniformLocation(m_program, "lightConstant"),0.25f);       // Constant used for attenuation, taken from lecture notes
    glUniform1f(glGetUniformLocation(m_program, "lightLinear"),0.7f);          // Constant used for attenuation, taken from lecture notes
    glUniform1f(glGetUniformLocation(m_program, "lightQuadratic"),1.0f);       // Constant used for attenuation, taken from lecture notes

    /// So for some reason the transformations here are done translation, rotation then scale, whereas online im reading scale, rotation, translation
    // TRS is done in reverse is a quirk of this specific method of creating the model matrix in OpenGL
    // Order of rotations is incredibly important and was discovered through trial and error
    // Concatenate matrices
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, m_scale);
    
    glm::mat4 mvp = camera.ProjectionMatrix() * camera.BuildViewMat() * modelMatrix;
    glUniformMatrix4fv(glGetUniformLocation(m_program,"modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(m_program,"mvp"), 1, GL_FALSE, &mvp[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, m_mesh->m_vertCount);
    ProfilerService::GetInstance()->StopTimer(profiler);
}
