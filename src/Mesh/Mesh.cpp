//
// Created by Jack Davidson on 04/06/2020.
//

#include "Mesh.h"

Mesh::Mesh(std::string filepath)
{
    m_manager = MeshManager::GetInstance();
    m_key = m_manager->Request(filepath);
}

Mesh::Mesh(const Mesh &cp)
{
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
}

Mesh::~Mesh(){
    m_manager->Dispose(m_key);
}

GLuint Mesh::GetVao()
{
    return m_manager->m_data.At(m_key).m_vao;
}

int Mesh::GetVertCount()
{
    return m_manager->m_data.At(m_key).m_vertCount;
}
