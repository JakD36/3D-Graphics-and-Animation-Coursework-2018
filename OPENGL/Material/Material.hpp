//
//  Material.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

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

#include "shaderLoader.hpp"


using namespace std;

class Material{
public:
    glm::vec3 m_ka;                                   // Ambient material constant
    glm::vec3 m_kd;                                   // Diffraction material constant
    glm::vec3 m_ks;                                   // Specular material constant
    GLfloat m_shininess;                              // Shininess constant of material
    
    Material(string materialName);
};

#endif /* Material_hpp */
