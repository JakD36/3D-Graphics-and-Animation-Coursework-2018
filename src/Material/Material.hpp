//
//  Material.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Material{
public:
    glm::vec3 m_ka;                                   // Ambient material constant
    glm::vec3 m_kd;                                   // Diffraction material constant
    glm::vec3 m_ks;                                   // Specular material constant
    GLfloat m_shininess;                              // Shininess constant of material
    
    Material(std::string materialName);
};

#endif /* Material_hpp */
