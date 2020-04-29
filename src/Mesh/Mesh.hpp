//
//  Mesh.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GL/glew.h>
#include <string>
#include <vector>

class Mesh{
    
public:
    int m_vertCount;

    GLuint          m_buffer;                      // Buffer to store the vertices, uvs and the normals for the model
    GLuint          m_vao; 

    std::vector<float> Load(std::string meshName) noexcept;
    std::vector<float> LoadAssimp(std::string meshName) noexcept;
    Mesh(std::string meshName) noexcept;
    ~Mesh() noexcept;
};

#endif /* Mesh_hpp */
