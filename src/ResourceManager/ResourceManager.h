//
// Created by Jack Davidson on 04/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RESOURCEMANAGER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RESOURCEMANAGER_H

#include "SparseVector.h"
#include <string>
#include <sys/stat.h>

template <class T>
class ResourceManager {
private:
    ResourceManager<T>(){}
    inline static ResourceManager<T>* m_instance = nullptr;
public:
    SparseVector<T> m_data;
    static ResourceManager<T>* GetInstance()
    {
        if(m_instance == nullptr)
        {
            m_instance = new ResourceManager();
        }
        return m_instance;
    }

    int Request(std::string filepath){
        for(int i = 0; i < m_data.size(); ++i)
        {
            if(m_data[i].m_key == filepath){
                ++m_data[i].m_count;
                return m_data.KeyAt(i);
            }
        }
        size_t key = m_data.Add(std::move(T(filepath)));
        ++m_data.At(key).m_count;
        return key;
    }

    void Dispose(int key){
        if(--m_data.At(key).m_count == 0)
        {
            m_data.Remove(key);
        }
    }

    void UpdateModified(){
        for(int i = 0; i < m_data.size(); ++i)
        {
            // Check if modified and reload if needed
            struct stat buf;
            stat(m_data[i].m_key.c_str(), &buf);

            if(m_data[i].m_lastModified != buf.st_mtime)
            {
                m_data[i].m_lastModified = buf.st_mtime;
                m_data[i] = T(m_data[i].m_key);
            }
        }
    }
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RESOURCEMANAGER_H
