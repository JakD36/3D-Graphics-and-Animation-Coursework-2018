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

#include "../Utils/ProfileService.h"
#include "../ResourceManager/ResourceService.hpp"

class Mesh{
    
public:
    int m_vertCount;

    GLuint          m_buffer;                      // Buffer to store the vertices, uvs and the normals for the model
    GLuint          m_vao; 

    std::vector<float> Load(string meshName);

    Mesh(string meshName);
};

#endif /* Mesh_hpp */
