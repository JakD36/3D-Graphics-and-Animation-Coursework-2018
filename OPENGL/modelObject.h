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

enum lightType {point,spot};
const int LIGHTSN = 3;

struct lightStruct{
public:
    lightType type = lightType::point; // 0 is point light, 1 is spotlight
    static glm::vec3 ia;
    glm::vec3 position = glm::vec3(1.0f,1.0f,1.0f);;
    glm::vec3 direction = glm::vec3(0.0f,0.0f,0.0f);;
    glm::vec3 id = glm::vec3(3.0f,3.0f,3.0f);
    glm::vec3 is = glm::vec3(3.0f,3.0f,3.0f);
};


class modelObject{
protected:
    std::vector < glm::vec3 > out_vertices;
    std::vector < glm::vec2 > out_uvs;
    std::vector < glm::vec3 > out_normals;
    GLuint          texture[1];            // texture name
    GLuint          program;
    GLuint          vao;
    GLuint          buffer[3];
    
    GLint           mv_location;
    GLint           modelLocation;
    GLint           proj_location;
    GLint           tex_location;
    
public:
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    GLfloat shininess;
    
    modelObject();
    void initModel(string,string,string); // initialise the modelObject with model and its shaders
    void initTexture(string); // provide texture for model
    void getUniLocation(); // get the uniform locations for model
    bool load(string); // load and parse .obj file
    void checkErrorShader(GLuint shader);
    string readShader(string fileName);
    bool loadMat(string);
    void setupRender(glm::mat4&, lightStruct[], glm::vec3&);
    virtual void render(glm::mat4&,glm::mat4&, lightStruct[], glm::vec3&) const =0;
};

#endif /* modelObject_h */
