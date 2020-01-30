#ifndef Lights_hpp
#define Lights_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <gli/gli.hpp>
#include <GLM/gtx/transform.hpp>

enum lightType {point,spot};    // Tells program if light is a point or spot light
const int LIGHTSN = 4;          // Number of the lights in the scene, defines the length of the array

const int lightStructByteSize = 96;

struct lightStruct{             // Struct to store details on each light
public:
    int lightOn = true;        // Allows us to be able switch lights on and off
    lightType type = lightType::point; // 0 is point light, 1 is spotlight. Default is point

    float padding1;
    float padding2;

    // 16
    glm::vec3 position = glm::vec3(1.0f,1.0f,1.0f); // Position of the light source
    float padding11 = 1.0f;
    // 16
    glm::vec3 direction = glm::vec3(0.0f,0.0f,0.0f);// Its direction, if it has one
    float padding12 = 1.0f;
    // 16
    float spotCutOff;
    float spotOuterCutOff;

    float padding3;
    float padding4;
    // 16
    glm::vec3 id = glm::vec3(3.0f,3.0f,3.0f);       // difraction intensity
    float padding13 = 1.0f;
    glm::vec3 is = glm::vec3(3.0f,3.0f,3.0f);
    float padding14 = 1.0f;
};

static glm::vec3 ia = glm::vec3(0.0f,1.0f,0.2f);        // Ambient Intensity, a static variable that is the same for all lights and used only the once



#endif