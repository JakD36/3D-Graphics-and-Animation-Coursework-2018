//
// Created by Jack Davidson on 14/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MATERIALRESOURCE_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MATERIALRESOURCE_H


#include "../../ResourceManager/Resource.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class MaterialResource : public Resource{
public:
    glm::vec3 m_ka; // Ambient material constant
    glm::vec3 m_kd; // Diffraction material constant
    glm::vec3 m_ks; // Specular material constant
    GLfloat m_shininess; // Shininess constant of material

    MaterialResource(std::string materialName);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MATERIALRESOURCE_H
