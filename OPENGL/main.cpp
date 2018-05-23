#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "sceneGraph.hpp"
#include "scene1.hpp"
#include "controller.hpp"
#include "keyboardAndMouse.hpp"


// VARIABLES

shaderLoader* shaderLoader::instance = NULL;

glm::vec3 lightStruct::ia = glm::vec3(0.0f,1.0f,0.2f); // we assign the static variable for the light struct out with the any functions

//glm::vec3 posOnSphere(float radius,float yaw,float pitch);
//void printVec3(glm::vec3 vec3,string str1,string str2,string str3);


// Our prototypes for functions used throughout the program, mainly the callbacks to handle user input
void errorCallbackGLFW(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
void debugGL();
static void APIENTRY openGLDebugCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const GLvoid* userParam);


void initOpenGL();
void initFramebuffer();
void hintsGLFW();
void endProgram();
void render(sceneGraph* scene);


GLFWwindow*             window;                     // Window the app will be displayed in
int                     windowWidth = 640;          // width of the window
int                     windowHeight = 480;         // height of the window
float                   aspect;                     // aspect ratio = width/height for exaple 4:3 or 16:9
glm::mat4               proj_matrix;                // Will be used in handling perspective into the scene?


// framebuffer variables, these all handle the framebuffer
GLuint            framebuffer;
GLuint            framebufferTexture;
GLuint            depthbuffer;
GLuint            displayVao;
GLuint            displayBuffer[2];
std::vector < glm::vec2 > displayVertices;
std::vector < glm::vec2 > displayUvs;
GLuint            displayProgram;
controller* mycontroller;


int main()
{
    initOpenGL();
    
    scene1 scene;
    mycontroller = new keyboardAndMouse(window,&scene);
    
    bool running = true;
    do {                                        // run until the window is closed
        double currentTime = glfwGetTime();     // retrieve timelapse
        glfwPollEvents();                       // poll callbacks I believe
        scene.update(currentTime);              // update (physics, animation, structures, etc)
        
        render(&scene);
        
        running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);    // exit if escape key pressed
        running &= (glfwWindowShouldClose(window) != GL_TRUE);
    } while (running);
    
    return 0;
}

void initOpenGL(){
    if (!glfwInit()) {                                  // Checking for GLFW
        cout << "Could not initialise GLFW...";
    }
    glfwSetErrorCallback(errorCallbackGLFW);            // Setup a function to catch and display all GLFW errors.
    hintsGLFW();                                        // Setup glfw with various hints.
                                                        // Start a window using GLFW
    string title = "My OpenGL Application";
    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    if (!window) {                                      // Window or OpenGL context creation failed
        cout << "Could not initialise GLFW...";
        endProgram();
        //return 0;
    }
    
    glfwMakeContextCurrent(window);                     // making the OpenGL context current
    
    // Start GLEW (note: always initialise GLEW after creating your window context.)
    glewExperimental = GL_TRUE;                         // hack: catching them all - forcing newest debug callback (glDebugMessageCallback)
    GLenum errGLEW = glewInit();
    if (GLEW_OK != errGLEW) {                           // Problems starting GLEW?
        cout << "Could not initialise GLEW...";
        endProgram();
    }
    
    //debugGL();
    
    // Setup all the message loop callbacks.
    glfwSetWindowSizeCallback(window, onResizeCallback);            // Set callback for resize
    glfwSetKeyCallback(window, onKeyCallback);                      // Set Callback for keys
    glfwSetMouseButtonCallback(window, onMouseButtonCallback);      // Set callback for mouse click
    glfwSetCursorPosCallback(window, onMouseMoveCallback);          // Set callback for mouse move
    glfwSetScrollCallback(window, onMouseWheelCallback);            // Set callback for mouse wheel.
                                                                    //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    // Set mouse cursor.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // Remove curser for FPS cam
    
    
    // Calculate proj_matrix for the first time.
    aspect = (float)windowWidth / (float)windowHeight;
    proj_matrix =  glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
    
    glfwSwapInterval(1);    // Ony render when synced (V SYNC)
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_STEREO, GL_FALSE);
    
    initFramebuffer();              // load textures, models,lights, shaders, all of this is done in this method in the init.cpp file
}

void hintsGLFW() {
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);            // Create context in debug mode - for debug message callback
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // On windows machine course uses version 4.5 on mac i need to use 4.2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1 );
    
    // Following two lines are required for running on mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void initFramebuffer() {
    
    // Framebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    
    //Setup the framebuffer using the following code taken from the the lecture notes and code
    
    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glGenTextures(1,&framebufferTexture);
    
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,windowWidth,windowHeight,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    
    // filtering needed - future lecture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Depth buffer texture    - Need to attach depth too otherwise depth testing will not be performed.
    glGenRenderbuffers(1, &depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);
    
    displayVertices.push_back(glm::vec2(-1.0f, 1.0f));
    displayVertices.push_back(glm::vec2(-1.0f,-1.0f));
    displayVertices.push_back(glm::vec2( 1.0f,-1.0f));
    displayVertices.push_back(glm::vec2(-1.0f, 1.0f));
    displayVertices.push_back(glm::vec2( 1.0f,-1.0f));
    displayVertices.push_back(glm::vec2( 1.0f, 1.0f));
    
    displayUvs.push_back(glm::vec2(0.0f, 1.0f));
    displayUvs.push_back(glm::vec2(0.0f, 0.0f));
    displayUvs.push_back(glm::vec2(1.0f, 0.0f));
    displayUvs.push_back(glm::vec2(0.0f, 1.0f));
    displayUvs.push_back(glm::vec2(1.0f, 0.0f));
    displayUvs.push_back(glm::vec2(1.0f, 1.0f));
    
    glGenBuffers(2,displayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 displayVertices.size()*sizeof(glm::vec2),
                 &displayVertices[0],
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 displayUvs.size()*sizeof(glm::vec2),
                 &displayUvs[0],
                 GL_STATIC_DRAW);
    
    
    glGenVertexArrays(1,&displayVao);
    glBindVertexArray(displayVao);
    glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    
    //load shaders
    displayProgram = glCreateProgram();
    
    shaderLoader* shaderInst = shaderLoader::getInstance();
    
    string dvs_text = shaderInst->readShader("Shaders/vs_display.glsl");
    const char* dvs_source = dvs_text.c_str();
    GLuint dvs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(dvs, 1, &dvs_source, NULL);
    glCompileShader(dvs);
    shaderInst->checkErrorShader(dvs);
    glAttachShader(displayProgram, dvs);
    
    string dfs_text = shaderInst->readShader("Shaders/fs_display.glsl");
    const char* dfs_source = dfs_text.c_str();
    GLuint dfs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dfs, 1, &dfs_source, NULL);
    glCompileShader(dfs);
    shaderInst->checkErrorShader(dfs);
    glAttachShader(displayProgram, dfs);
    
    glLinkProgram(displayProgram);
    glUseProgram(displayProgram);
}

void onResizeCallback(GLFWwindow* window, int w, int h) {
    windowWidth = w;
    windowHeight = h;
    
    aspect = (float)w / (float)h;
    proj_matrix = glm::perspective(glm::radians(50.0f), aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    mycontroller->onMouseButton(window, button, action, mods);
}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
    mycontroller->onMouseMove(window, x, y ); // So we can swap out the controller and will have no effect on the callback
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
}




glm::vec3 posOnSphere(float radius,float yaw,float pitch){
    glm::vec3 pos;
    pos.x = radius* sin( glm::radians(yaw) ) * cos(glm::radians(pitch) );
    pos.y = radius* sin( glm::radians(pitch) );
    pos.z = radius* cos( glm::radians(yaw) ) * cos(glm::radians(pitch) );

    return pos;
}

void printVec3(glm::vec3 vec3,string str1,string str2,string str3){
    // Handy for debugging to find out what different vec3s are
    cout<<str1<<" >> "<<vec3.x<<"\t"<<str2<<" >> "<<vec3.y<<"\t"<<str3<<" >> "<<vec3.z<<endl;
}

void endProgram() {
    glfwMakeContextCurrent(window);             // destroys window handler
    glfwTerminate();                            // destroys all windows and releases resources.
}









////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Taken from F21GA 3D Graphics and Animation Labs

void debugGL() {
    //Output some debugging information
    cout << "VENDOR: " << (char *)glGetString(GL_VENDOR) << endl;
    cout << "VERSION: " << (char *)glGetString(GL_VERSION) << endl;
    cout << "RENDERER: " << (char *)glGetString(GL_RENDERER) << endl;
    
    // Enable Opengl Debug
    //glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback((GLDEBUGPROC)openGLDebugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
}

static void APIENTRY openGLDebugCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const GLvoid* userParam) {
    
    cout << "---------------------opengl-callback------------" << endl;
    cout << "Message: " << message << endl;
    cout << "type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cout << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cout << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cout << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            cout << "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            cout << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            cout << "OTHER";
            break;
    }
    cout << " --- ";
    
    cout << "id: " << id << " --- ";
    cout << "severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
            cout << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "HIGH";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            cout << "NOTIFICATION";
    }
    cout << endl;
    cout << "-----------------------------------------" << endl;
}

void errorCallbackGLFW(int error, const char* description) {
    cout << "Error GLFW: " << description << "\n";
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



void render(sceneGraph* scene){
    // So now to render to the framebuffer texture instead of screen
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,framebufferTexture,0);
    
    glm::vec4 black = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ); // our background colour will be black
    
    glViewport(0, 0, windowWidth, windowHeight); // Convert all our projected coordinates to screen coordinates for the texture
    glClearBufferfv(GL_COLOR, 0, &black[0]);
    static const GLfloat one = 1.0f;
    
    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    glm::vec3 cameraPos = scene->getCamera().getPosition();
    glm::vec3 cameraFront = scene->getCamera().getFront();
    
    // To create our camera, we use the lookAt function generate the viewMatrix
    // It takes 3 inputs, the position of the camera, the point in space it is facing and which direction is up, so its orientated properly
    glm::mat4 viewMatrix = glm::lookAt(cameraPos,                       // eye
                                       cameraPos+cameraFront,           // centre, we need to use the pos+cameraFront to make sure its pointing to the right point in space
                                       glm::vec3(0.0f, 1.0f, 0.0f));    // up
    
    // Render each object
    // As we have put pointers to every object, we can use polymorphism to call the setupRender and the render methods of each object, which do differnet things depending on if its an instanced object or single use.
    vector<modelObject*> Objs = scene->getObjs();
    
    
    
    lightStruct* plight = scene->getLights();
    lightStruct lights[LIGHTSN];
    for(int n = 0; n < LIGHTSN; n++){
        lights[n] = *(plight+n);
    }
    
    
    
    for(int n = 0;n<Objs.size();n++){
        Objs[n]->setupRender(proj_matrix,lights,cameraPos);
        Objs[n]->render(proj_matrix,viewMatrix,lights,cameraPos);
    }
    
    // SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(-windowWidth*2, -windowHeight*2, windowWidth*4, windowHeight*4);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); //not needed as we are just displaying a single quad
    glUseProgram(displayProgram);
    glBindVertexArray(displayVao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);                // swap buffers (avoid flickering and tearing)
}
