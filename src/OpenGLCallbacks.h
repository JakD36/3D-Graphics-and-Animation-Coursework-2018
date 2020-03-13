//
// Created by Jack Davidson on 12/03/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_OPENGLCALLBACKS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_OPENGLCALLBACKS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Controllers/Controller.hpp"
#include "Views/Renderer.hpp"

void OnResizeCallback(GLFWwindow* window, int w, int h);
// Our prototypes for OpenGL functions used throughout the program, mainly the callbacks to handle user input
void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void OnMouseMoveCallback(GLFWwindow* window, double x, double y);
void OnMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void ErrorCallbackGLFW(int error, const char* description);
void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);

// Global variables
extern GLFWwindow* window;
extern int windowWidth;
extern int windowHeight;

extern Renderer* myView; // is global to be accessible through callbacks
extern Controller* myController; // myController is global to be accessible through the callbacks

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_OPENGLCALLBACKS_H