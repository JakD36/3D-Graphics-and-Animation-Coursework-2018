//
//  sceneGraph.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "sceneGraph.hpp"

// Default constructor
sceneGraph::sceneGraph(){
    playerPosition = glm::vec3(0.0f,1.6f,0.0f);
}

// TODO: Add copy constructor, allow for deep copy of object so to avoid any issues with two scenes using the same memory on the heap

sceneGraph::~sceneGraph(){
    
    // Make sure to delete all the objects from the heap!
    // Otherwise we will have a memory leak
    // Any objects not added to the Objs list, make sure to add them to the relevant destructor so that there are no memory leaks
    for(int n = 0; n < Objs.size(); n++){
        delete Objs[n];
        Objs[n] = NULL;
    }
}

// Returns the objects of the scene, this is the same for every scene inheriting from this abstract
vector<modelObject*> sceneGraph::getObjs(){
    return Objs;
}

glm::vec3 sceneGraph::posOnSphere(float radius,float yaw,float pitch){
    glm::vec3 pos;
    pos.x = radius* sin( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    pos.y = radius* sin( glm::radians(pitch) );
    pos.z = radius* cos( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    
    return pos;
}

void sceneGraph::printVec3(glm::vec3 vec3,string str1,string str2,string str3){
    // Handy for debugging to find out what different vec3s are
    cout<<str1<<" >> "<<vec3.x<<"\t"<<str2<<" >> "<<vec3.y<<"\t"<<str3<<" >> "<<vec3.z<<endl;
}


lightStruct* sceneGraph::getLights(){
    return lights;
}

glm::vec3 sceneGraph::getPlayerPosition(){
    return playerPosition;
}
