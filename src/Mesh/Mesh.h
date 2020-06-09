//
// Created by Jack Davidson on 04/06/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MESH_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MESH_H


#include "../ResourceManager/MeshManager.h"
#include <string>

class Mesh {
private:
    size_t m_key;
    MeshManager* m_manager;
public:
    Mesh(std::string filepath);
    Mesh(const Mesh &cp); // Copy
    ~Mesh();

    GLuint GetVao();
    int GetVertCount();
};


#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_MESH_H
