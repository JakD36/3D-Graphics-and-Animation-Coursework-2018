//
//  modelObject.h
//  OPENGLClassTest
//
//  Created by Jack Davidson on 09/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#ifndef modelObject_h
#define modelObject_h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <gli/gli.hpp>
#include <GLM/gtx/transform.hpp>
#include "OBJParser.h"

class modelObject{
private:
    
public:
    std::vector < glm::vec3 > out_vertices;
    std::vector < glm::vec2 > out_uvs;
    std::vector < glm::vec3 > out_normals;
    GLuint          texture[1];            // texture name
    GLuint          program;
    GLuint          vao;
    GLuint          buffer[2];
    GLint           mv_location;
    GLint           proj_location;
    GLint           tex_location;
    
    glm::vec3 position  = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 rotation  = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 scale     = glm::vec3(1.0f,1.0f,1.0f);
    
    // extra variables for this example
    GLuint        matColor_location;
    GLuint        lightColor_location;
    
    modelObject();
    void initModel(string,string,string); // initialise the modelObject with model and its shaders
    void initTexture(string); // provide texture for model
    void getUniLocation(); // get the uniform locations for model
    bool load(string); // load and parse .obj file
    void checkErrorShader(GLuint shader);
    string readShader(string fileName);
    void virtual render(glm::mat4&,glm::mat4&);
};

#endif /* modelObject_h */
