////
//// Created by Jack Davidson on 04/06/2020.
////
//
//#include "ResourceManager.h"
//
//template <class T>
//ResourceManager<T>* ResourceManager<T>::GetInstance()
//{
//    if(m_instance == nullptr)
//    {
//        m_instance = new ResourceManager();
//    }
//    return m_instance;
//}
//
//template <class T>
//int ResourceManager<T>::Request(std::string filepath)
//{
//    for(int i = 0; i < m_data.size(); ++i)
//    {
//        if(m_data[i].m_key == filepath){
//            ++m_data[i].m_count;
//            return i;
//        }
//    }
//    int index = m_data.size();
//    m_data.Add(T(filepath));
//    return index;
//}
//
//template <class T>
//void ResourceManager<T>::Dispose(int key)
//{
//    m_data.Remove(key);
//}
//
//template <class T>
//void ResourceManager<T>::UpdateModified()
//{
//    for(int i = 0; i < m_data.size(); ++i)
//    {
//        // Check if modified and reload if needed
//        struct stat buf;
//        stat(m_data[i].m_key.c_str(), &buf);
//
//        if(m_data[i].m_lastModified != buf.st_mtime)
//        {
//            m_data[i].m_lastModified = buf.st_mtime;
//            m_data[i] = T(m_data[i].m_key);
//        }
//    }
//}