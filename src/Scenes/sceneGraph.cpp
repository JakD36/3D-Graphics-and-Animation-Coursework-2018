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
    p_camera = new Camera();
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
vector<GameObject*> SceneGraph::GetObjs(){
    return m_Objs;
}

LightStruct* SceneGraph::GetLights(){
    return m_lights;
}

glm::vec3 SceneGraph::GetPlayerPosition(){
    return m_playerPosition;
}

Camera* SceneGraph::GetCamera()
{
    return p_camera;
}