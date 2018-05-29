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

#include "shaderLoader.hpp"


enum lightType {point,spot};    // Tells program if light is a point or spot light
const int LIGHTSN = 4;          // Number of the lights in the scene, defines the length of the array


struct lightStruct{             // Struct to store details on each light
public:
    bool lightOn = true;        // Allows us to be able switch lights on and off
    lightType type = lightType::point; // 0 is point light, 1 is spotlight. Default is point
    
    static glm::vec3 ia;        // Ambient Intensity, a static variable that is the same for all lights and used only the once
    glm::vec3 position = glm::vec3(1.0f,1.0f,1.0f); // Position of the light source
    glm::vec3 direction = glm::vec3(0.0f,0.0f,0.0f);// Its direction, if it has one
    glm::vec3 id = glm::vec3(3.0f,3.0f,3.0f);       // difraction intensity
    glm::vec3 is = glm::vec3(3.0f,3.0f,3.0f);       // specular intensity
};

class modelObject{              // modelObject handles each graphic object,
protected:
    std::vector < glm::vec3 > out_vertices;         // Vertices of our objects mesh
    std::vector < glm::vec2 > out_uvs;              // uvs coordinates for texture mapping
    std::vector < glm::vec3 > out_normals;          // Normals to each plane in our mesh
    GLuint          texture[1];                     //
    GLuint          program;                        // Program to attach our shaders to
    GLuint          vao;                            //
    GLuint          buffer[3];                      // Buffer to store the vertices, uvs and the normals for the model
    
    
public:
    glm::vec3 ka;                                   // Ambient material constant
    glm::vec3 kd;                                   // Diffraction material constant
    glm::vec3 ks;                                   // Specular material constant
    GLfloat shininess;                              // Shininess constant of material
    
    modelObject();
    void initModel(string,string,string);           // initialise the modelObject with model and its shaders
    void initTexture(string);                       // provide texture for model
    bool load(string);                              // load and parse .obj file
    bool loadMat(string);                           // Load the material file, from the provided pathname string
    void setupRender(glm::mat4&, lightStruct[], glm::vec3&);    // Setup all the uniforms, so that the shaders can access the relevant info, when needed
    
    virtual void render(glm::mat4&,glm::mat4&, lightStruct[], glm::vec3&) = 0; // virtual method, allows us to change the method later on.
    // This way specifically doesnt provide a definition to the render method, turning the modelObject into an abstract Class
};

#endif /* modelObject_h */
