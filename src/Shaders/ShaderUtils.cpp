#include "ShaderUtils.h"

bool CheckDriverSupportsBinaryPrograms(){
    GLint formats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &formats);
    if( formats < 1 ) {
        printf("Driver does not support any binary formats.\n");
        return false;
    }

    printf("Driver supports binary formats.\n");
    return true;
}

void SaveCompiledProgramToFile(GLuint program,std::string filepath){
    // Get the binary length
    GLint length = 0;
    glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);

    // Retrieve the binary code
    std::vector<GLubyte> buffer(length);
    GLenum format = 0;
    glGetProgramBinary(program, length, NULL, &format, buffer.data());

    // Write the binary to a file.
    std::ofstream out;

    out.open(filepath.c_str(), std::ios::binary);
    if(out){
        out.write( reinterpret_cast<char *>(buffer.data()), length );
    }
    else{
        printf("Failed to open %s",filepath.c_str());
    }

    out.close();
}

GLuint LoadProgramFromBinary(std::string filepath){
    GLuint program = glCreateProgram();

    // Load binary from file
    std::ifstream file;

    file.open(filepath, std::ios::binary);

    if(file){
        std::istreambuf_iterator<char> startIt(file), endIt;
        std::vector<char> buffer(startIt, endIt);  // Load file

        GLenum format = 0;
        // Install shader binary
        glProgramBinary(program, format, buffer.data(), buffer.size() );

        // Check for success/failure
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if( GL_FALSE == status ) {
            // Handle failure ...
        }
    }else{
        printf("Failed to open %s",filepath.c_str());
    }

    file.close();

    return program;
}

void CheckShaderLog(GLuint shader) {
    // Get the length of the info log in the shader
    GLint maxLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    if (maxLength > 0) { // If the length is > 0, we have an error or warning from the compiler
        // Init a string for it
        std::vector<GLchar> errorLog(maxLength);
        // Get the log file
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << "--------------Shader compilation error-------------" << std::endl;
        std::cout << errorLog.data() << std::endl;
        std::cout << "----------------------- END -----------------------" << std::endl;
    }
}

GLuint CompileShader(const GLenum type, const std::string& source){
    GLuint shader = glCreateShader(type);
    const char * constantSrc = source.c_str();
    glShaderSource(shader, 1, &constantSrc, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &status);
    printf("Shader type %d output %d\n",type,status);

    CheckShaderLog(shader);

    return shader;
}

void CheckProgramLog(GLuint program){
    // Get the length of the info log in the program
    GLint maxLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    if (maxLength > 0) { // If the length is > 0, we have an error or warning from the linker
        // Init a string for it
        std::vector<GLchar> log(maxLength);
        // Get the log file
        glGetShaderInfoLog(program, maxLength, &maxLength, &log[0]);
        std::cout << "-------------- Shader Link Error -------------" << std::endl;
        std::cout << log.data() << std::endl;
        std::cout << "--------------------- END --------------------" << std::endl;
    }
}

void LinkProgram(const GLuint program, const GLuint vert, const GLuint frag)
{
    glAttachShader(program, vert);
    glAttachShader(program, frag);

    glProgramParameteri(program,GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

    glLinkProgram(program);

    GLint isLinked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);

    if(isLinked == GL_FALSE)
        printf("Error program did not link");

    CheckProgramLog(program);

    glDetachShader(program,vert);
    glDetachShader(program,frag);
}

std::string LoadShader(std::string filepath) {
    std::ifstream file; // input filestream
    std::string line;
    std::string output = "";

    file.open(filepath);

    if(file){
        while (getline(file, line)) {
            output.append(line + "\n");
        }
    }
    else{
        printf("Could not find file >> %s",filepath.c_str());
    }
    file.close();

    return output;
}

void RecompileShader(GLuint shader, std::string path, const char* fallback)
{
    std::string source = LoadShader(path);
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

