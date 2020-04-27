#include "OpenGLCallbacks.h"
#include <cstdio>
#include "Utils/ProfilerService.h"
#include "Views/Renderer.hpp"
#include "Controllers/Controller.hpp"

// callback functions call the methods of the controller or Renderer, so that functionality can be swapped as need be by changing the object
void OnResizeCallback(GLFWwindow* window, int w, int h) {
    PROFILE(profiler,"On Resize Callback");
    // Call methods of the renderers used
    s_view->SetWindowDimensions(w, h);
    ENDPROFILE(profiler);
}

void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    s_controller->OnKey(window, key, scancode, action, mods);
}

void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    s_controller->OnMouseButton(window, button, action, mods);
}

void OnMouseMoveCallback(GLFWwindow* window, double x, double y) {
    s_controller->OnMouseMove(window, x, y ); // So we can swap out the controller and will have no effect on the callback
}

void OnMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
}

void ErrorCallbackGLFW(int error, const char* description) {
    printf("Error GLFW: %s\n",description);
}

void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{

    printf("---------------------opengl-callback------------\n");
    printf("Message: %s",message);
    printf("type: ");
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            printf("ERROR");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            printf("DEPRECATED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            printf("UNDEFINED_BEHAVIOR");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            printf("PORTABILITY");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            printf("PERFORMANCE");
            break;
        case GL_DEBUG_TYPE_OTHER:
            printf("OTHER");
            break;
    }
    printf(" --- ");

    printf("id: %d --- ",id);
    printf("severity: ");
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            printf("LOW");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            printf("MEDIUM");
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            printf("HIGH");
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            printf("NOTIFICATION");
    }
    printf("\n");
    printf("-----------------------------------------\n");
}


