//
//  MeshResource.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef MeshResource_hpp
#define MeshResource_hpp

#include <GL/glew.h>
#include <string>
#include <vector>
#include <string>
#include "../../ResourceManager/Resource.h"

enum class VertexAttrib
{
    POSITION = 1 << 0,
    UV = 1 << 1,
    NORMALS = 1 << 2,
    TANGENT = 1 << 3,
    BITANGENT = 1 << 4,
    COLOUR = 1 << 5
};


/// File based mesh information, only changed external to application
class MeshResource : public Resource{
private:
    MeshResource(const MeshResource &cp);
    MeshResource& operator=(const MeshResource &cp) noexcept;
public:
    int m_vertCount;
    int m_attributeFlags;

    GLuint m_vao;
    GLuint m_buffer; // Buffer to store the vertices, uvs and the normals for the model
    GLuint m_indexBuffer;

    void Load(std::string meshName, int attribs, std::vector<float> &interleavedData, std::vector<int> &indices) noexcept;
    MeshResource(std::string metadataFilepath) noexcept;
    MeshResource(MeshResource &&mv);
    MeshResource& operator=(MeshResource&& mv) noexcept;
    ~MeshResource() noexcept;
};

#endif /* Mesh_hpp */
