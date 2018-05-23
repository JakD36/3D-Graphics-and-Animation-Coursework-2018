//
//  sceneGraph.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "sceneGraph.hpp"


sceneGraph::sceneGraph(){
    
}

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

void sceneGraph::turnCamera(double xoffset, double yoffset){
    sceneCamera.turnCamera(xoffset,yoffset);
}

camera sceneGraph::getCamera(){
    return sceneCamera;
}
