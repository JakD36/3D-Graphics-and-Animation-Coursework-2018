//
//  ShaderLoader.cpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#include "ShaderLoader.hpp"

ShaderLoader::ShaderLoader(){ // Default constructor!
}

ShaderLoader* ShaderLoader::GetInstance(){
    if(m_instance == NULL){
        m_instance = new ShaderLoader();
    }
    return m_instance;
}

string ShaderLoader::ReadShader(string fileName) {
    fstream file;
    string output ="";          // String we will read each individual line of the shader too
    string wholeCode ="";       // We can append each line to this string so that the entire shader can be output,
    file.open(fileName);        // Open the provided shader file
    
    if(!file){                  // Check if the file opened
        cout<<"Could not find file >> "<<fileName<<endl;
    }
    else{                       // If it did, the read each line and append it to the final string that will be returned
        while (getline(file, output)) {
            wholeCode.append(output + "\n");
            //cout << output << endl;
        }
    }
    
    file.close();               // Once finished reading the shader close the file
    
    return wholeCode;           // Output the code
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Taken from F21GA 3D Graphics and Animation Labs

void ShaderLoader::CheckErrorShader(GLuint shader) {
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

// End of code taken from lectures.

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

