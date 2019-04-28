//
//  sceneGraph.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "sceneGraph.hpp"

// Default constructor
SceneGraph::SceneGraph(){
    m_playerPosition = glm::vec3(0.0f,1.6f,0.0f);
    string meshPath = "Set/newTorch.obj";
    string matPath = "Materials/newTorch.mtl";
    string texPath = "Textures/newTorchCol.ktx";
    string vsPath = "Shaders/vs.glsl";
    string fsPath = "Shaders/fs.glsl";
    
    Mesh* mesh = new Mesh("Set/newTorch.obj");
    Material* mat = new Material("Materials/newTorch.mtl");
    Texture* tex = new Texture("Textures/newTorchCol.ktx");
    
    VertexShader* vs = new VertexShader("Shaders/vs.glsl");
    FragShader* fs = new FragShader("Shaders/fs.glsl");
    
    ShaderPipeline* pipeline = new ShaderPipeline(vs,fs);
    
    m_gameObject = new GameObject(mesh,mat,tex,pipeline);
}

// TODO: Add copy constructor, allow for deep copy of object so to avoid any issues with two scenes using the same memory on the heap

SceneGraph::~SceneGraph(){
    
    // Make sure to delete all the objects from the heap!
    // Otherwise we will have a memory leak
    // Any objects not added to the Objs list, make sure to add them to the relevant destructor so that there are no memory leaks
    for(int n = 0; n < m_Objs.size(); n++){
        delete m_Objs[n];
        m_Objs[n] = NULL;
    }
}

// Returns the objects of the scene, this is the same for every scene inheriting from this abstract
vector<modelObject*> SceneGraph::GetObjs(){
    return m_Objs;
}

lightStruct* SceneGraph::GetLights(){
    return m_lights;
}

glm::vec3 SceneGraph::GetPlayerPosition(){
    return m_playerPosition;
}
