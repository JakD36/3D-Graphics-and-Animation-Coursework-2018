//
// Created by Jack Davidson on 04/06/2020.
//

#include "MeshManager.h"

MeshManager * MeshManager::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new MeshManager();
    }
    return m_instance;
}

int MeshManager::Request(std::string filepath)
{
    for(int i = 0; i < m_data.size(); ++i)
    {
        if(m_data[i].m_key == filepath){
            ++m_data[i].m_count;
            return i;
        }
    }
    int index = m_data.size();
    m_data.Add(MeshResource(filepath));
    return index;
}

void MeshManager::Dispose(int key)
{
    m_data.Remove(key);
}