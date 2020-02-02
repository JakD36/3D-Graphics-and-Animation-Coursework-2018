#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <unordered_map>
#include <string>
#include <GL/glew.h>

#include "ShaderUtils.h"

using namespace std;

class ShaderManager {
private:
    unordered_map<string,GLuint> m_programs;
    unordered_map<string,GLuint> m_shaders;

    GLuint m_defaultVertShader;
    GLuint m_defaultFragShader;

    const char* k_defaultVert = "#version 410 core\n"
                                "layout (location = 0) in vec4 position;\n"
                                "uniform mat4 mvp;\n"
                                "void main(void)\n"
                                "{\n"
                                "    gl_Position = mvp * position;\n"
                                "}";

    const char* k_defaultFrag = "#version 410 core\n"
                                "out vec4 color;\n"
                                "void main(void)\n"
                                "{\n"
                                "    color = vec4(1,0,1,1);\n"
                                "}";

    static ShaderManager* m_instance;
    ShaderManager();
public:
    static ShaderManager* GetInstance();

    GLuint RequestProgram(string vertPath, string fragPath);
    void RecompileShaders();
};

#endif
