#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <vector>
#include <GL/glew.h>

/// Struct to store file information for a shader.
struct ShaderInfo
{
public:
    std::string path;
    GLuint shader;
    time_t lastModified;
};

struct ProgramInfo
{
public:
    std::string path;
    GLuint program;
};

class ShaderManager {
private:
    std::vector<ShaderInfo> m_shaderInfo;
    std::vector<ProgramInfo> m_programs;

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

    inline static ShaderManager* m_instance = NULL;
    ShaderManager();
    int FindShader(std::string id);
    int FindProgram(std::string id);

public:
    static ShaderManager* GetInstance();

    /// Searches for a program that uses the provided shaders to return or compiles and links a new program
    /// @returns A program, using the provided shaders if they compiled, or a program with the default shaders if not
    GLuint RequestProgram(std::string vertPath, std::string fragPath);

    /// Performs a check to see if shaders need recompiled.
    void Update();

    /// Updates the shaders and relinks the programs to use the new shaders
    void RecompileAllProgramShaders();
    std::vector<ProgramInfo>* GetShaderPrograms();
};

#endif
