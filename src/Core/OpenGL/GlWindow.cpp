//
// Created by Jack Davidson on 07/08/2020.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GlWindow.h"
#include "../../Utils/DebugUtils.h"
#include "../WindowEvent.h"
#include <cstdio>

void SetupOpenGLCallbacks(GLFWwindow* window);
void SetupOpenGLDebug();
void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);

GlWindow::GlWindow(std::string title, int width, int height)
{
    if(s_windowCount == 0)
    {
        bool success = glfwInit();
        assertm(success,"Glfw could not be initialised!")
    }

    glfwSetErrorCallback([](int error, const char* description){
        printf("Error GLFW: %s\n",description);
    });

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );

#ifdef __APPLE__
    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    assertm(m_window,"Could not create window")

    glfwMakeContextCurrent(m_window);

    if(s_windowCount == 0)
    {
        glewExperimental = GL_TRUE; // hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
        GLenum glewStatus = glewInit();
        assertm(GLEW_OK == glewStatus,"Could not initialise GLEW")

        SetupOpenGLDebug();
    }

    glfwSetWindowUserPointer(m_window,&m_windowData);

    SetupOpenGLCallbacks(m_window);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSwapInterval(1);    // Ony render when synced (V SYNC each 1 frame)
    glfwWindowHint(GLFW_SAMPLES, 32);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);

    ++s_windowCount;
    m_lastTime = glfwGetTime();
    m_deltaTime = 0.0f;
}

void GlWindow::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);

    float currentTime = glfwGetTime();
    m_deltaTime = currentTime - m_lastTime;
    m_lastTime = currentTime;
}

GlWindow::~GlWindow()
{
    glfwDestroyWindow(m_window);

    if(--s_windowCount == 0)
        glfwTerminate();
}

void GlWindow::RegisterEventListener(std::function<void(WindowEvent& event)> func)
{
    m_windowData.m_eventHandler = func;
}

float GlWindow::GetDeltaTime() {
    return m_deltaTime;
}

void* GlWindow::GetNativeWindow(){
    return m_window;
}

void GlWindow::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled);
}

void GlWindow::SetCursor(bool enabled)
{
    glfwSetInputMode(m_window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void SetupOpenGLCallbacks(GLFWwindow* window)
{
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
        auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowResizeEvent event(width, height);
        windowData.m_eventHandler(event);
    });

    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* window, int width, int height){
        auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        FramebufferResizeEvent event(width, height);
        windowData.m_eventHandler(event);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        switch(action)
        {
            case GLFW_PRESS:
            {
                auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
                KeyPressedEvent event(key);
                windowData.m_eventHandler(event);
                break;
            }
            case GLFW_RELEASE:
            {
                auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
                KeyReleasedEvent event(key);
                windowData.m_eventHandler(event);
                break;
            }
            // TODO: Could handle the key being held down by using the GLFW_REPEAT, but instead going to update the keystatus, in input class
            default:
                break;
        }
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
        switch(action)
        {
            case GLFW_PRESS:
            {
                auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseButtonPressedEvent event(button);
                windowData.m_eventHandler(event);
                break;
            }
            case GLFW_RELEASE:
            {
                auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseButtonReleasedEvent event(button);
                windowData.m_eventHandler(event);
                break;
            }
        }
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y){
        auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMoveEvent event(x, y);
        windowData.m_eventHandler(event);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* window){
        auto& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        windowData.m_eventHandler(event);
    });
}

void SetupOpenGLDebug()
{
    //Output some debugging information
    printf("VENDOR %s\n",(char *)glGetString(GL_VENDOR));
    printf("VERSION %s\n",(char *)glGetString(GL_VERSION));
    printf("RENDERER %s\n",(char *)glGetString(GL_RENDERER));

    // Enable Opengl Debug
    if(glDebugMessageCallback)
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
    }
    else
    {
        printf("OpenGL Debug Output not available\n");
    }
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
