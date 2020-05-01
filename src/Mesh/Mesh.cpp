//
//  Mesh.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#include <GL/glew.h>
#include "Mesh.hpp"
#include "../Utils/DebugUtils.h"
#include <iostream>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

Mesh::Mesh(string meshName, std::vector<VertexAttrib> attrib) noexcept{
    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(1,&m_buffer); // Generate the buffer to store the vertices, uvs and normals

    m_attribs = attrib;

    vector<float> interleavedData = Load(meshName);
//    vector<float> interleavedData = LoadAssimp(meshName);
 
    // For debug we can uncomment to see how many vertices, UVs and Normals are in each object
    const int size[]{3,2,3,3,3,3};
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    glBufferData(GL_ARRAY_BUFFER,                       // store the vertices in the first part of the buffer
                 interleavedData.size()*sizeof(float), // vertices size * size of vec3 tells us how much space in the buffer to allocate
                 &interleavedData[0],                      // Where to start in the vertices vector
                 GL_STATIC_DRAW);

    int total = 0;
    for(int i = 0; i < m_attribs.size(); ++i)
    {
        total += size[(int)m_attribs[i]];
    }

    int offset = 0;
    for(int i = 0; i < m_attribs.size(); ++i)
    {
        glVertexAttribPointer(i, size[(int)m_attribs[i]] , GL_FLOAT, GL_FALSE, sizeof(float) * total, (void*)(sizeof(float) * offset));
        glEnableVertexAttribArray(i);
        offset += size[(int)m_attribs[i]];
    }
}

std::vector<float> Mesh::LoadAssimp(string meshName) noexcept
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(meshName, aiProcess_Triangulate | aiProcess_CalcTangentSpace );
    vector<float> interleavedData;
    vector<int> indices;
    for(int i = 0; i < scene->mMeshes[0]->mNumFaces; ++i)
    {
        auto face = scene->mMeshes[0]->mFaces[i];
        for(int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    interleavedData.reserve(8 * indices.size());
    for(int i = 0; i < indices.size(); ++i)
    {
        for(int j = 0; j < m_attribs.size(); ++j) {
            switch (m_attribs[j]) {
                case VertexAttrib::POSITION: {
                    auto vert = scene->mMeshes[0]->mVertices[indices[i]];
                    interleavedData.push_back(vert.x);
                    interleavedData.push_back(vert.y);
                    interleavedData.push_back(vert.z);
                    break;
                }
                case VertexAttrib::UV: {
                    auto uvs = scene->mMeshes[0]->mTextureCoords[0][indices[i]];
                    interleavedData.push_back(uvs.x);
                    interleavedData.push_back(uvs.y);
                    break;
                }
                case VertexAttrib::NORMALS: {
                    auto normals = scene->mMeshes[0]->mNormals[indices[i]];
                    interleavedData.push_back(normals.x);
                    interleavedData.push_back(normals.y);
                    interleavedData.push_back(normals.z);
                    break;
                }
                case VertexAttrib::TANGENT: {
                    auto tangents = scene->mMeshes[0]->mTangents[indices[i]];
                    interleavedData.push_back(tangents.x);
                    interleavedData.push_back(tangents.y);
                    interleavedData.push_back(tangents.z);
                    break;
                }
                case VertexAttrib::BITANGENT: {
                    auto bitangents = scene->mMeshes[0]->mBitangents[indices[i]];
                    interleavedData.push_back(bitangents.x);
                    interleavedData.push_back(bitangents.y);
                    interleavedData.push_back(bitangents.z);
                    break;
                }
                case VertexAttrib::COLOUR:
                {
                    assertm(false,"Undefined attribute");
                    break;
                }
            }
        }
    }
    m_vertCount = indices.size();
    return interleavedData;
}
// TODO: Calculate Bit tangents and tangents myself!
std::vector<float> Mesh::Load(string meshName) noexcept{
    // Variables
    FILE* pfile = nullptr; // using stdio and fscanf which means formatted scan file
    int result;         // for taking output of fscanf function
    char line[256];     // char array of size 256 for storing each line of the file (limited to lines of 256 in length which could be an issue)
    
    vector<glm::vec3> tmpV; //Temp vertex indices
    vector<glm::vec2> tmpVt; // temp vertex texture indices
    vector<glm::vec3> tmpVn; // temp vertex normal indices
    
    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    
    int matches;
    
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    vector<glm::vec3> verts, normals, tangents, bitangents;
    vector<glm::vec2> uvs;
    
    vector<float> interleavedData;
    pfile = fopen(meshName.c_str(),"r"); // open the file with read access

    assertm(pfile!= nullptr,("Could not find file " + meshName));

    if(pfile == nullptr){ // if the file doesnt open when using fopen
        cout<<"Could not find file >> "<<meshName<<endl; // print error and name of file that failed to open
        return interleavedData; // exit function as it has failed
    }
    else{
        do{ // if file does open loop through each line of the file while EOF has not been reached
            result = fscanf(pfile,"%s",line); // %s refers to keep scanning until first whitespace
                                              // we can then compare the first section of text to the different headers for each line
            
            // "v" means the following text is vertexs
            if(strcmp(line,"v") == 0){ // vertex indices
                glm::vec3 vertex; // create temporary storage for vertices
                
                fscanf(pfile,"%f %f %f\n",&vertex.x,&vertex.y,&vertex.z); // take the vertices and assign to vertex variable
                                                                          // line will be in format of %f %f %f\n ie three floats seperated by spaces
                tmpV.push_back(vertex); // copy the vertex from this line to the back of the vertex vector
                
            }
            // "vt" means the following text is uvs
            else if(strcmp(line,"vt") == 0){ // vertex texture indices (u,v) glm::vec2
                glm::vec2 uv; // Create temporary storage for vertices
                
                fscanf(pfile,"%f %f\n",&uv.x,&uv.y); // assign the uvs to the uv variable as with vertex line
                tmpVt.push_back(uv); // copy temporary uv to the back of the uv vector
            }
            // "vn" means the following text is normals
            else if(strcmp(line,"vn") == 0){ // vertex normal indices (x,y,z) glm::vec3, might not be unit vectors
                glm::vec3 normal; // create temporary storage for normals
                
                fscanf(pfile,"%f %f %f\n",&normal.x,&normal.y,&normal.z); // assign the normals to the normal variable as with vertex line
                tmpVn.push_back(normal); // copy the temporary normal to the normal vector
            }
            else if(strcmp(line,"f") == 0){ // Polygonal face element
                
                // so there are multiple formats for these lines so we use sscanf to go through each line after the first whitespace
                // the formats are
                
                // %d/%d/%d %d/%d/%d %d/%d/%d\n ie we have vertex.x/uv.x/normal.x vertex.y/uv.y/normal.y vertex.z/uv.z/normal.z\n
                
                // %d//%d %d//%d %d//%d\n ie we have vertex.x//normal.x vertex.y//normal.y vertex.z//normal.z\n
                
                // %d/%d %d/%d %d/%d\n ie we have vertex.x/uv.x vertex.y/uv.y vertex.z/uv.z\n
                
                // %d %d %d\n ie we have vertex.x vertex.y vertex.z\n
                
                result = fscanf(pfile,"%[^\n]", line); // store everything until the end of the line in the char array line
                if((matches = sscanf(line,"%d/%d/%d %d/%d/%d %d/%d/%d\n", // Format of expected line, ie 3 sets of vertex,uv and normal
                                     &vertexIndex[0],&uvIndex[0],&normalIndex[0], // Assign .x values for each
                                     &vertexIndex[1],&uvIndex[1],&normalIndex[1], // assign .y values for each
                                     &vertexIndex[2],&uvIndex[2],&normalIndex[2]) // assign .z values for each
                    ) == 9){ // sscanf returns how many of the variables in the line follow the pattern we have given if there 9 matches we have the right format
                    
                    // add each vertex index into the vertexIndices vector
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    
                    // add each uv index into the uvIndices vector
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    
                    // add each normal index into the normalIndices vector
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                    
                }
                else if((matches = sscanf(line,"%d//%d %d//%d %d//%d\n", // format of expected line ie 3 sets of vertex and normals
                                          &vertexIndex[0],&normalIndex[0], // assign .x values for each
                                          &vertexIndex[1],&normalIndex[1], // assign .y values for each
                                          &vertexIndex[2],&normalIndex[2]) // assign .z values for each
                         ) == 6){ // sscanf returns how many of the variables in the line follow the pattern we have given if there 6 matches we have the right format
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    normalIndices.push_back(normalIndex[0]);
                    
                    vertexIndices.push_back(vertexIndex[1]);
                    normalIndices.push_back(normalIndex[1]);
                    
                    vertexIndices.push_back(vertexIndex[2]);
                    normalIndices.push_back(normalIndex[2]);
                    
                }
                else if(sscanf(line,"%d/%d %d/%d %d/%d\n", // format of expected line ie 3 sets of vertex and uvs
                               &vertexIndex[0],&uvIndex[0], // assign .x values for each
                               &vertexIndex[1],&uvIndex[1], // assign .y values for each
                               &vertexIndex[2],&uvIndex[2]) // assign .z values for each
                        == 6){ // sscanf returns how many of the variables in the line follow the pattern we have given if there 6 matches we have the right format
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    
                }
                
                else if(sscanf(line,"%d %d %d\n", // format of expected line ie 3 vertices
                               &vertexIndex[0],
                               &vertexIndex[1],
                               &vertexIndex[2])
                        == 3){
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                }
                else{ // If the lines dont match any of the given formats then the error will be printed along with the line and the number of matches
                    cout<<"Does not match parser result >>"<<endl;
                    cout<<line<<endl;
                    cout<<"This gave "<< matches<<" matches"<<endl;
                }
            }
        } while (result != EOF);

        // Now to go through vertex, uv and normal and push each to the vectors that will be outputted from the object
        for(unsigned int i=0; i<vertexIndices.size();i+=3){ // loops through the vertexIndices in batches of 3, so we can reverse them so that everything is displayed correctly
            
            // the index of the vertex position is vertexIndices[i]
            // so the position is temp_vertices[vertexIndex-1], -1 because C++ starts at 0 whereas obj starts at 1
            
            unsigned int vertexIndex = vertexIndices[i]; // Creates an index and assigns 2 above the current place in loop so we start at the end
            glm::vec3 vertex = tmpV[vertexIndex-1]; // stores the tmpV and subtracts 1 from index as C++ starts at 0 not 1
            verts.push_back(vertex); // this adds the position to the back of the vertex
            
            vertexIndex = vertexIndices[i+1]; // so we get the index for the middle vertex by moving up 1 indices
            vertex = tmpV[vertexIndex-1];
            verts.push_back(vertex); // this makes the position of our new vertex
            
            vertexIndex = vertexIndices[i+2]; // finally indexes the first value in the 3 and adds it to the back of the 3 completing reverse of batch
            vertex = tmpV[vertexIndex-1];
            verts.push_back(vertex); // this makes the position of our new vertex
        }
        
        // Repeats the above done for vertices for both normals and uvs if we have them
        if(!tmpVn.empty()){ // If we have normals push them
            for(unsigned int i=0; i<normalIndices.size();i+=3){
                // the index of the vertex position is vertexIndices[i]
                // so the position is temp_vertices[vertexIndex-1] -1 because C++ starts at 0 whereas obj starts at
                
                unsigned int normalIndex = normalIndices[i];
                glm::vec3 normal = tmpVn[normalIndex-1];
                normals.push_back(normal);
                
                normalIndex = normalIndices[i+1];
                normal = tmpVn[normalIndex-1];
                normals.push_back(normal);
                
                normalIndex = normalIndices[i+2];
                normal = tmpVn[normalIndex-1];
                normals.push_back(normal);
            }
        }
        if(!tmpVt.empty()){
            for(unsigned int i=0; i<uvIndices.size();i+=3){
                // the index of the vertex position is vertexIndices[i]
                // so the position is temp_vertices[vertexIndex-1] -1 because C++ starts at 0 whereas obj starts at 1
                
                unsigned int uvIndex = uvIndices[i];
                glm::vec2 uv = tmpVt[uvIndex-1];
                uvs.push_back(uv);
                
                uvIndex = uvIndices[i+1];
                uv = tmpVt[uvIndex-1];
                uvs.push_back(uv);
                
                uvIndex = uvIndices[i+2];
                uv = tmpVt[uvIndex-1];
                uvs.push_back(uv);
            }
        }

        for(unsigned int i=0; i<verts.size();i+=3)
        {
            auto deltaUv1 = uvs[i + 1] - uvs[i];
            auto deltaUv2 = uvs[i + 2] - uvs[i];

            auto E1 = verts[i + 1] - verts[i];
            auto E2 = verts[i + 2] - verts[i];

            float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
            glm::vec3 tangent = glm::normalize((E1 * deltaUv2.y - E2 * deltaUv1.y)*r);

            tangent = glm::normalize(tangent - normals[i] * glm::dot(normals[i], tangent)); // Makes sure that the tangent is orthogonal, 90 degrees to normal

            glm::vec3 bitangent = glm::normalize(glm::cross(tangent,normals[i]));
            
            // Same Tangent and bit tangent for all 3 verts!
            tangents.push_back(tangent);
            tangents.push_back(tangent);
            tangents.push_back(tangent);
            bitangents.push_back(bitangent);
            bitangents.push_back(bitangent);
            bitangents.push_back(bitangent);
        }

        for(int i = 0; i < verts.size(); ++i)
        {
            for(int j = 0; j < m_attribs.size(); ++j)
            {
                switch(m_attribs[j])
                {
                    case VertexAttrib::POSITION:
                        interleavedData.push_back(verts[i].x);
                        interleavedData.push_back(verts[i].y);
                        interleavedData.push_back(verts[i].z);
                        break;
                    case VertexAttrib::UV:
                        interleavedData.push_back(uvs[i].x);
                        interleavedData.push_back(uvs[i].y);
                        break;
                    case VertexAttrib::NORMALS:
                        interleavedData.push_back(normals[i].x);
                        interleavedData.push_back(normals[i].y);
                        interleavedData.push_back(normals[i].z);
                        break;
                    case VertexAttrib::TANGENT:
                        interleavedData.push_back(tangents[i].x);
                        interleavedData.push_back(tangents[i].y);
                        interleavedData.push_back(tangents[i].z);
                        break;
                    case VertexAttrib::BITANGENT:
                        interleavedData.push_back(bitangents[i].x);
                        interleavedData.push_back(bitangents[i].y);
                        interleavedData.push_back(bitangents[i].z);
                        break;
                    case VertexAttrib::COLOUR:
                        // TODO: ???
                        break;
                }
            }
        }
        m_vertCount = verts.size() * 3;

        fclose(pfile); // closes file and returns true to indicate that the import was successful
        return interleavedData;
    }
}

Mesh::~Mesh() noexcept
{
    glDeleteBuffers(1,&m_buffer);
    glDeleteVertexArrays(1,&m_vao);
}
