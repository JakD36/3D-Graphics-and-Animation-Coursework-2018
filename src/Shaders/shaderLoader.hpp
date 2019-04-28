//
//  ShaderLoader.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef ShaderLoader_hpp
#define ShaderLoader_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <gli/gli.hpp>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*
 shaderLoader is a singleton to prevent, multiple shader loaders being instantiated across the different objects.
 Uses lazy instantiation, so not to take up any space until it is required.
*/
class ShaderLoader{
private:
    ShaderLoader(); // Constructor needs to be private so can only create it through the getInstance method
    static ShaderLoader* m_instance; // A pointer to our instance of the singleton
    
    // Any other variables for the singleton
    
public:
    static ShaderLoader* GetInstance(); // The method to access the Singleton must be static and return a pointer to our instance
    
    // Any other methods for the singleton!
    string ReadShader(string fileName);     // Reads the GLSL shaders so they can be compiled and attached to the programs for each model
    void CheckErrorShader(GLuint shader);
};


#endif /* ShaderLoader_hpp */
