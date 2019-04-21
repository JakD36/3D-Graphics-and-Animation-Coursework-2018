//
//  Mesh.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <gli/gli.hpp>
#include <GLM/gtx/transform.hpp>

#include "../Shaders/shaderLoader.hpp"

class Mesh{
    
public:
    std::vector < glm::vec3 > out_vertices;         // Vertices of our objects mesh
    std::vector < glm::vec2 > out_uvs;              // uvs coordinates for texture mapping
    std::vector < glm::vec3 > out_normals;          // Normals to each plane in our mesh
    GLuint          m_buffer[3];                      // Buffer to store the vertices, uvs and the normals for the model
    GLuint          m_vao; 
    bool Load(string meshName);
    
    
    

    Mesh(string meshName);
};

#endif /* Mesh_hpp */
