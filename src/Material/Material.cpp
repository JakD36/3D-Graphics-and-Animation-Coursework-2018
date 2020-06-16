//
//  Material.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include "Material.hpp"
#include <iostream>

using namespace std;

Material::Material(std::string filepath){
    m_manager = ResourceManager<MaterialResource>::GetInstance();
    m_key = m_manager->Request(filepath);
}

Material::Material(const Material &cp){
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
}

Material& Material::operator=(const Material &cp){
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
    return *this;
}

Material::Material(Material &&mv)
{
    *this = std::move(mv);
}

Material& Material::operator=(Material &&mv)
{
    m_manager = nullptr;
    m_key = -1;
    return *this;
}

Material::~Material(){
    m_manager->Dispose(m_key);
}

glm::vec3 Material::GetAmbient(){ return m_manager->m_data.At(m_key).m_ka; }
glm::vec3 Material::GetDiffuse(){ return m_manager->m_data.At(m_key).m_kd; }
glm::vec3 Material::GetSpecular(){ return m_manager->m_data.At(m_key).m_ks; }
GLfloat Material::GetShininess(){ return m_manager->m_data.At(m_key).m_shininess; }