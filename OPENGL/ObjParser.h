//
//  ObjParser.h
//  OPENGL
//
//  Created by Jack Davidson on 29/09/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#ifndef ObjParser_h
#define ObjParser_h
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <GLM/glm.hpp>

using namespace std;

class ObjParser{
private:
    string name;
    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;
public:
    ObjParser(string name);
    bool load();
    void clear();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getUvs();
    std::vector<glm::vec3> getNormals();
};

#endif /* ObjParser_h */
