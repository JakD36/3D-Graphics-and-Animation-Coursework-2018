//
//  readShader.cpp
//  OPENGL
//
//  Created by Jack Davidson on 26/09/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "GLapp.h"
#include "modelObject.h"

string GLapp::readShader(string fileName) {
    fstream file;
    string output ="";
    string wholeCode ="";
    file.open(fileName);
    if(!file){
        cout<<"Could not find file >> "<<fileName<<endl;
    }
    else{
        while (getline(file, output)) {
            wholeCode.append(output + "\n");
            //cout << output << endl;
        }
    }
    file.close();
    
    return wholeCode;
}

void GLapp::checkErrorShader(GLuint shader) {
    // Get log lenght
    GLint maxLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    // Init a string for it
    std::vector<GLchar> errorLog(maxLength);
    if (maxLength > 0) {
        // Get the log file
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        cout << "--------------Shader compilation error-------------\n";
        cout << errorLog.data();
    }
}

string modelObject::readShader(string fileName) {
    fstream file;
    string output ="";
    string wholeCode ="";
    file.open(fileName);
    if(!file){
        cout<<"Could not find file >> "<<fileName<<endl;
    }
    else{
        while (getline(file, output)) {
            wholeCode.append(output + "\n");
            //cout << output << endl;
        }
    }
    file.close();
    
    return wholeCode;
}

void modelObject::checkErrorShader(GLuint shader) {
    // Get log lenght
    GLint maxLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    // Init a string for it
    std::vector<GLchar> errorLog(maxLength);
    if (maxLength > 0) {
        // Get the log file
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        cout << "--------------Shader compilation error-------------\n";
        cout << errorLog.data();
    }
}
