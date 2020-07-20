#include "ShaderManager.h"
#include <sys/stat.h>

#include "ShaderUtils.h"
#include "../Profiling/ProfilerService.h"

using namespace std;

ShaderManager::ShaderManager()
{
    PROFILE(profiler,"ShaderManager Constructor");
    m_defaultVertShader = CompileShader(GL_VERTEX_SHADER, k_defaultVert);
    m_defaultFragShader = CompileShader(GL_FRAGMENT_SHADER, k_defaultFrag);
    ENDPROFILE(profiler);
}

int ShaderManager::FindShader(string id)
{
    PROFILE(p,"Find Shader");
    int count = m_shaderInfo.size();
    for(int i = 0; i < count; ++i)
    {
        if(m_shaderInfo[i].path == id)
        {
            ENDPROFILE(p);
            return i;
        }
    }

    ENDPROFILE(p);
    return -1;
}

int ShaderManager::FindProgram(string id)
{
    PROFILE(p,"Find Program");
    int count = m_shaderInfo.size();
    for(int i = 0; i < count; ++i)
    {
        if(m_programs[i].path == id)
        {
            ENDPROFILE(p);
            return i;
        }
    }
    ENDPROFILE(p);
    return -1;
}

void ShaderManager::Update()
{
    PROFILE(p,"ShaderManager Update");

    int shaderCount = m_shaderInfo.size();
    bool recompileRequired = false;
    for(int i = 0; i < shaderCount; ++i)
    {
        struct stat buf;
        stat(m_shaderInfo[i].path.c_str(),&buf);

        if(m_shaderInfo[i].lastModified != buf.st_mtime)
        {
            recompileRequired = true;
            m_shaderInfo[i].lastModified = buf.st_mtime;
        }
    }

    if(recompileRequired)
    {
        RecompileAllProgramShaders();
    }
    ENDPROFILE(p);
}

GLuint ShaderManager::RequestProgram(string vertPath, string fragPath)
{
    PROFILE(p,"ShaderManager Request Program");

    // Program
    string programName = vertPath + "+" + fragPath;
    int result = FindProgram(programName);
    if(result >= 0)
    {
        ENDPROFILE(p);
        return m_programs[result].program;
    }

    GLuint program = glCreateProgram();
    m_programs.push_back(
            ProgramInfo {
                programName,
                program
            });

    // Shaders
    GLuint vert, frag;

    int searchIndex = FindShader(vertPath);
    if(searchIndex >= 0)
    {
        vert = m_shaderInfo[searchIndex].shader;
    }
    else
    {
        string source = LoadShader(vertPath);
        vert = CompileShader(GL_VERTEX_SHADER, source);

        struct stat buf;
        stat(vertPath.c_str(),&buf);

        ShaderInfo newShader
        {
            vertPath,
            vert,
            buf.st_mtime
        };
        m_shaderInfo.push_back(newShader);
    }

    searchIndex = FindShader(fragPath);

    if(searchIndex >= 0)
    {
        frag = m_shaderInfo[searchIndex].shader;
    }
    else
    {
        string source = LoadShader(fragPath);
        frag = CompileShader(GL_FRAGMENT_SHADER, source);

        struct stat buf;
        stat(vertPath.c_str(),&buf);

        ShaderInfo newShader{
            fragPath,
            frag,
            buf.st_mtime
        };
        m_shaderInfo.push_back(newShader);
    }

    GLint vertStatus, fragStatus;
    glGetShaderiv(vert,GL_COMPILE_STATUS, &vertStatus);
    glGetShaderiv(frag,GL_COMPILE_STATUS, &fragStatus);

    if(vertStatus == GL_TRUE && fragStatus == GL_TRUE)
    {
        LinkProgram(program, vert, frag);
    }
    else
    {
        LinkProgram(program, m_defaultVertShader, m_defaultFragShader);
    }

    ENDPROFILE(p);
    return program;
}

ShaderManager* ShaderManager::GetInstance()
{
    if (m_instance == NULL){
        m_instance = new ShaderManager();
    }
    return m_instance;
}

void ShaderManager::RecompileAllProgramShaders()
{
    PROFILE(p,"ShaderManager Recompile shaders");
    int programCount = m_programs.size();
    for(int i = 0; i < programCount; ++i)
    {
        string programName = m_programs[i].path;
        GLuint program = m_programs[i].program;

        GLuint vert,frag;

        int index = programName.find("+");
        string vertPath = programName.substr(0,index);
        string fragPath = programName.substr(index+1,programName.length() - index+1);

        bool found = false;
        int shaderCount = m_shaderInfo.size();
        int searchIndex;
        
        for(searchIndex = 0; searchIndex < shaderCount; ++searchIndex)
        {
            if(m_shaderInfo[searchIndex].path == vertPath){
                found = true;
                break;
            }
        }
        if(found)
        {
            string shaderPath = m_shaderInfo[searchIndex].path;
            GLuint shader = m_shaderInfo[searchIndex].shader;

            GLint type;
            glGetShaderiv(shader, GL_SHADER_TYPE, &type);

            if(type == GL_VERTEX_SHADER)
            {
                RecompileShader(shader, shaderPath, k_defaultVert);
                vert = shader;
            }
            else if(type == GL_FRAGMENT_SHADER)
            {
                RecompileShader(shader, shaderPath, k_defaultFrag);
                frag = shader;
            }
        }

        found = false;
        shaderCount = m_shaderInfo.size();
        for(searchIndex = 0; searchIndex < shaderCount; ++searchIndex)
        {
            if(m_shaderInfo[searchIndex].path == fragPath){
                found = true;
                break;
            }
        }
        if(found)
        {
            string shaderPath = m_shaderInfo[searchIndex].path;
            GLuint shader = m_shaderInfo[searchIndex].shader;

            GLint type;
            glGetShaderiv(shader, GL_SHADER_TYPE, &type);

            if(type == GL_VERTEX_SHADER)
            {
                RecompileShader(shader, shaderPath, k_defaultVert);
                vert = shader;
            }
            else if(type == GL_FRAGMENT_SHADER)
            {
                RecompileShader(shader, shaderPath, k_defaultFrag);
                frag = shader;
            }
        }

        LinkProgram(program,vert,frag);
    }
    ENDPROFILE(p);
}

vector<ProgramInfo> ShaderManager::GetShaderPrograms()
{
    return m_programs;
}