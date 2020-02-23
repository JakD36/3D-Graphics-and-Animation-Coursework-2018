#ifndef ShaderUtils_h
#define ShaderUtils_h

#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <GL/glew.h>

bool CheckDriverSupportsBinaryPrograms();
void SaveCompiledProgramToFile(GLuint program,std::string filepath);
GLuint LoadProgramFromBinary(std::string filepath);
GLuint CompileShader(const GLenum type,const std::string& source);
void LinkProgram(const GLuint program, const GLuint vert, const  GLuint frag);
std::string LoadShader(std::string filepath);
void CheckShaderLog(GLuint shader);
void CheckProgramLog(GLuint program);
void RecompileShader(GLuint shader, std::string path, const char* fallback);
#endif