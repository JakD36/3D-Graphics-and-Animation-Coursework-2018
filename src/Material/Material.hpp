//
//  Material.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "../ResourceManager/ResourceManager.h"
#include <string>
#include "MaterialResource.h"

class Material{
public:
    size_t m_key;
    ResourceManager<MaterialResource>* m_manager;

    Material(std::string materialName);
    Material(const Material &cp);
    Material& operator=(const Material &cp);
    ~Material();

    Material(Material &&mv);
    Material& operator=(Material &&cp);


    glm::vec3 GetAmbient();
    glm::vec3 GetDiffuse();
    glm::vec3 GetSpecular();
    GLfloat GetShininess();
};

#endif /* Material_hpp */
