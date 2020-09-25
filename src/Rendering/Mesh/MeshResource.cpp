//
//  MeshResource.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include <GL/glew.h>
#include "MeshResource.hpp"
#include "../../Utils/DebugUtils.h"
#include <iostream>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <json.hpp>
#include <fstream>

using namespace std;

MeshResource::MeshResource(string metadataFilepath) noexcept  : Resource(metadataFilepath){

    m_attributeFlags = 0;

    nlohmann::json js;
    std::fstream file(metadataFilepath);
    assertm(file.is_open(),("RenderPass Json file did not open. "));
    file >> js;

    auto attribStrs = js["vertexAttributes"];
    for(int i = 0; i < attribStrs.size();++i)
    {
        if(attribStrs[i] == "POSITION")
            m_attributeFlags |= (int)VertexAttrib::POSITION;
        else if(attribStrs[i] == "UV")
            m_attributeFlags |= (int)VertexAttrib::UV;
        else if(attribStrs[i] == "NORMALS")
            m_attributeFlags |= (int)VertexAttrib::NORMALS;
        else if(attribStrs[i] == "TANGENT")
            m_attributeFlags |= (int)VertexAttrib::TANGENT;
        else if(attribStrs[i] == "BITANGENT")
            m_attributeFlags |= (int)VertexAttrib::BITANGENT;
        else if(attribStrs[i] == "COLOUR")
            m_attributeFlags |= (int)VertexAttrib::COLOUR;
        else
            assertm(false,"Undefined attribute string found!");
    }

    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(1,&m_buffer); // Generate the buffer to store the vertices, uvs and normals
    glGenBuffers(1,&m_indexBuffer); // Generate the buffer to store indices

    vector<float> interleavedData;
    vector<int> indices;
    Load(js["filepath"],m_attributeFlags, interleavedData, indices);
 

    const int size[]{3,2,3,3,3,3};
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER,                       // store the vertices in the first part of the buffer
                 interleavedData.size()*sizeof(float), // vertices size * size of vec3 tells us how much space in the buffer to allocate
                 &interleavedData[0],                      // Where to start in the vertices vector
                 GL_STATIC_DRAW);

    int total = 0;
    for(int i = 0; i < 6; ++i)
    {
        total += size[i] * ((m_attributeFlags & (1 << i)) > 0 ? 1 : 0);
    }

    int offset = 0;
    for(int i = 0; i < 6; ++i)
    {
        if((m_attributeFlags & (1 << i)) > 0) // Set the stride and offsets for all the attributes
        {
            glVertexAttribPointer(i, size[i] , GL_FLOAT, GL_FALSE, sizeof(float) * total, (void*)(sizeof(float) * offset));
            glEnableVertexAttribArray(i);
            offset += size[i];
        }
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size()*sizeof(float),
                 &indices[0],
                 GL_STATIC_DRAW);
}

void MeshResource::Load(string meshName, int attribs, vector<float> &interleavedData, vector<int> &indices) noexcept
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(meshName, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

    for(int i = 0; i < scene->mMeshes[0]->mNumFaces; ++i)
    {
        auto face = scene->mMeshes[0]->mFaces[i];
        for(int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    interleavedData.reserve(8 * scene->mMeshes[0]->mNumVertices);

    auto& verts = scene->mMeshes[0]->mVertices;
    auto& uvs = scene->mMeshes[0]->mTextureCoords[0];
    auto& normals = scene->mMeshes[0]->mNormals;
    auto& tangents = scene->mMeshes[0]->mTangents;
    auto& bitangents = scene->mMeshes[0]->mBitangents;

    for(int i = 0; i < scene->mMeshes[0]->mNumVertices; ++i)
    {
        if((attribs & (int)VertexAttrib::POSITION) > 0)
        {
            interleavedData.push_back(verts[i].x);
            interleavedData.push_back(verts[i].y);
            interleavedData.push_back(verts[i].z);
        }
        if((attribs & (int)VertexAttrib::UV) > 0)
        {
            interleavedData.push_back(uvs[i].x);
            interleavedData.push_back(uvs[i].y);
        }
        if((attribs & (int)VertexAttrib::NORMALS) > 0)
        {
            interleavedData.push_back(normals[i].x);
            interleavedData.push_back(normals[i].y);
            interleavedData.push_back(normals[i].z);
        }
        if((attribs & (int)VertexAttrib::TANGENT) > 0)
        {
            interleavedData.push_back(tangents[i].x);
            interleavedData.push_back(tangents[i].y);
            interleavedData.push_back(tangents[i].z);
        }
        if((attribs & (int)VertexAttrib::BITANGENT) > 0)
        {
            interleavedData.push_back(bitangents[i].x);
            interleavedData.push_back(bitangents[i].y);
            interleavedData.push_back(bitangents[i].z);
        }
    }
    m_vertCount = indices.size();//scene->mMeshes[0]->mNumFaces * 3;
}


MeshResource::~MeshResource() noexcept
{
    glDeleteBuffers(1,&m_buffer);
    glDeleteVertexArrays(1,&m_vao);
}

MeshResource::MeshResource(const MeshResource &cp) : Resource(cp.m_key){} // TODO: ADD
MeshResource& MeshResource::operator=(const MeshResource &cp) noexcept{} // TODO: ADD

MeshResource::MeshResource(MeshResource &&mv) : Resource(mv.m_key){
    *this = std::move(mv);
}

MeshResource& MeshResource::operator=(MeshResource&& mv) noexcept{
    m_key = mv.m_key;
    m_lastModified = mv.m_lastModified;
    m_count = mv.m_count;
    mv.m_key = "";
    mv.m_lastModified = 0;
    mv.m_count = 0;

    m_attributeFlags = mv.m_attributeFlags;
    m_vertCount = mv.m_vertCount;
    m_vao = mv.m_vao;
    m_buffer = mv.m_buffer;

    mv.m_buffer = 0;
    mv.m_vao = 0;
    mv.m_attributeFlags = 0;
    mv.m_vertCount = 0;

    return *this;
}