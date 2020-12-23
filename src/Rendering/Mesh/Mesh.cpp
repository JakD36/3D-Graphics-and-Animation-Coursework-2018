//
// Created by Jack Davidson on 04/06/2020.
//

#include "Mesh.h"

Mesh::Mesh(std::string filepath)
{
    m_manager = ResourceManager<MeshResource>::GetInstance();
    m_key = m_manager->Request(filepath);
//    ++m_manager->m_data.At(m_key).m_count;
}

Mesh::Mesh(const Mesh &cp)
{
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
}

Mesh& Mesh::operator=(const Mesh &cp)
{
    m_manager = cp.m_manager;
    m_key = cp.m_key;
    ++m_manager->m_data.At(m_key).m_count;
    return *this;
}

Mesh::~Mesh(){
    m_manager->Dispose(m_key);
}

int Mesh::GetVertCount()
{
    return m_manager->m_data.At(m_key).m_vertCount;
}

void Mesh::Bind()
{
    glBindVertexArray(m_manager->m_data.At(m_key).m_vao);
}

void Mesh::Unbind()
{
    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glDrawElements(GL_TRIANGLES, GetVertCount(), GL_UNSIGNED_INT, 0);
}

