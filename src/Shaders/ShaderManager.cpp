#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
    ProfilerService* profilerInstance = ProfilerService::GetInstance();
    int profiler = profilerInstance->StartTimer("ShaderManager Constructor");
    m_defaultVertShader = CompileShader(GL_VERTEX_SHADER, k_defaultVert);
    m_defaultFragShader = CompileShader(GL_FRAGMENT_SHADER, k_defaultFrag);
    profilerInstance->StopTimer(profiler);
}

void ShaderManager::Update()
{
    ProfilerService* profilerInstance = ProfilerService::GetInstance();
    int profiler = profilerInstance->StartTimer("ShaderManager Update");

    int shaderCount = m_shaderInfo.size();
    bool recompileRequired = false;
    for(int i = 0; i < shaderCount; ++i)
    {
        struct stat buf;
        stat(m_shaderInfo[i].path.c_str(),&buf);

        if(m_shaderInfo[i].lastModified != buf.st_mtimespec.tv_sec)
        {
            recompileRequired = true;
            m_shaderInfo[i].lastModified = buf.st_mtimespec.tv_sec;
        }
    }

    if(recompileRequired)
    {
        RecompileShaders();
    }
    profilerInstance->StopTimer(profiler);
}

GLuint ShaderManager::RequestProgram(string vertPath, string fragPath)
{
    ProfilerService* profilerInstance = ProfilerService::GetInstance();
    int profiler = profilerInstance->StartTimer("ShaderManager Request Program");
    unordered_map<string, GLuint>::iterator result;

    // Program
    string programName = vertPath + "+" + fragPath;
    result = m_programs.find(programName);
    if(result != m_programs.end())
    {
        return result->second;
    }

    GLuint program = glCreateProgram();
    m_programs.emplace(programName,program);

    // Shaders
    GLuint vert, frag;

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
            buf.st_mtimespec.tv_sec
        };
        m_shaderInfo.push_back(newShader);
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
            buf.st_mtimespec.tv_sec
        };
        m_shaderInfo.push_back(newShader);
    }

    GLint vertStatus, fragStatus;
    glGetShaderiv(vert,GL_COMPILE_STATUS, &vertStatus);
    glGetShaderiv(frag,GL_COMPILE_STATUS, &fragStatus);

    if(vertStatus == GL_TRUE && fragStatus == GL_TRUE)
    {
        CreateProgram(program,vert,frag);
    }
    else
    {
        CreateProgram(program,m_defaultVertShader,m_defaultFragShader);
    }

    profilerInstance->StopTimer(profiler);
    return program;
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

    CheckProgramLog(program);

    glDetachShader(program,vert);
    glDetachShader(program,frag);
}

void ShaderManager::RecompileShaders()
{
    ProfilerService* profilerInstance = ProfilerService::GetInstance();
    int profiler = profilerInstance->StartTimer("ShaderManager Recompile shaders");
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

        RelinkProgram(program,vert,frag);
    }
    profilerInstance->StopTimer(profiler);
}

ShaderManager* ShaderManager::GetInstance()
{
    if (m_instance == NULL){
        m_instance = new ShaderManager();
    }
    return m_instance;
}