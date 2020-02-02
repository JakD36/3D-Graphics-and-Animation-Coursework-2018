#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    m_defaultVertShader = CompileShader(GL_VERTEX_SHADER, k_defaultVert);

    m_defaultFragShader = CompileShader(GL_FRAGMENT_SHADER, k_defaultFrag);
}

GLuint ShaderManager::RequestProgram(string vertPath, string fragPath)
{
    unordered_map<string, GLuint>::iterator result;

    string programName = vertPath + "+" + fragPath;
    result = m_programs.find(programName);
    if(result != m_programs.end())
    {
        return result->second;
    }

    GLuint vert, frag;

    result = m_shaders.find(vertPath);
    if(result != m_shaders.end())
    {
        vert = result->second;
    }
    else
    {
        string source = LoadShader(vertPath);
        vert = CompileShader(GL_VERTEX_SHADER, source);
        m_shaders.emplace(vertPath,vert);
    }

    result = m_shaders.find(fragPath);
    if(result != m_shaders.end())
    {
        frag = result->second;
    }
    else
    {
        string source = LoadShader(fragPath);
        frag = CompileShader(GL_FRAGMENT_SHADER, source);
        m_shaders.emplace(fragPath,frag);
    }

    GLint vertStatus, fragStatus;
    glGetShaderiv(vert,GL_COMPILE_STATUS, &vertStatus);
    glGetShaderiv(frag,GL_COMPILE_STATUS, &fragStatus);

    GLuint program = glCreateProgram();
    m_programs.emplace(programName,program);



    if(vertStatus == GL_TRUE && fragStatus == GL_TRUE)
    {
        CreateProgram(program,vert,frag);
        GLint isLinked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_TRUE)
        {
            return program;
        }
    }
    else
    {
        CreateProgram(program,m_defaultVertShader,m_defaultFragShader);
        GLint isLinked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if(isLinked == GL_TRUE)
        {
            return program;
        }
    }
}

void RecompileShader(GLuint shader, string path, const char* fallback)
{
    string source = LoadShader(path);
    const char* csrc = source.c_str();
    glShaderSource(shader,1,&csrc,NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &status);

    CheckShaderLog(shader);

    if(status == GL_FALSE)
    {
        glShaderSource(shader, 1, &fallback, NULL);
        glCompileShader(shader);
    }
}

void RelinkProgram(GLuint program, GLuint vert, GLuint frag)
{
    glAttachShader(program, vert);
    glAttachShader(program, frag);

    glProgramParameteri(program,GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

    glLinkProgram(program);

    GLint isLinked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

    if(isLinked == GL_FALSE)
    {
        // TODO: Use
    }

    CheckProgramLog(program);
}

// TODO: Fix Can't recompile shaders that were broken in the first place
void ShaderManager::RecompileShaders()
{
    unordered_map<string,GLuint>::iterator iter;
    for(iter = m_programs.begin(); iter != m_programs.end(); ++iter)
    {
        string programName = iter->first;
        GLuint program = iter->second;

        GLuint vert,frag;

        int index = programName.find("+");
        string vertPath = programName.substr(0,index);
        string fragPath = programName.substr(index+1,programName.length() - index+1);

        unordered_map<string,GLuint>::iterator result;
        result = m_shaders.find(vertPath);
        if(result != m_shaders.end())
        {
            string shaderPath = result->first;
            GLuint shader = result->second;

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

        result = m_shaders.find(fragPath);
        if(result != m_shaders.end())
        {
            string shaderPath = result->first;
            GLuint shader = result->second;

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

        RelinkProgram(program,vert,frag);
    }
}

ShaderManager* ShaderManager::GetInstance()
{
    if (m_instance == NULL){
        m_instance = new ShaderManager();
    }
    return m_instance;
}