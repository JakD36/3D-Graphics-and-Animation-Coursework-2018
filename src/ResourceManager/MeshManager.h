//
// Created by Jack Davidson on 04/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MESHMANAGER_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MESHMANAGER_H

#include "SparseVector.h"
#include "../Mesh/MeshResource.hpp"

class MeshManager {
private:
    MeshManager();
    inline static MeshManager* m_instance = nullptr;
public:
    SparseVector<MeshResource> m_data;
    static MeshManager* GetInstance();
    int Request(std::string key);
    void Dispose(int key);
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MESHMANAGER_H
