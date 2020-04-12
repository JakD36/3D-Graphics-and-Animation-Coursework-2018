//
// Created by Jack Davidson on 13/03/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_OPENGLSETUP_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_OPENGLSETUP_H

#include <GL/glew.h>

// Prototypes for setting up OpenGL and closing it down
GLFWwindow* InitOpenGL(int windowWidth, int windowHeight);
void HintsGLFW();
void SetupOpenglDebug();
void EndProgram(GLFWwindow* window);

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_OPENGLSETUP_H
