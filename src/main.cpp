#if defined(_WIN32)
    #define GLEW_STATIC
#endif

// OpenGL - glew, glfw and glm
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Workshop.h"

int main(int argc, char *argv[])
{
    Application *app = CreateApplication();
    app->Run();
    return 0;
}

