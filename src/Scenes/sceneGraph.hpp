//
//  sceneGraph.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 19/05/2018.
//  Copyright © 2018 Jack Davidson. All rights reserved.
//

#ifndef sceneGraph_hpp
#define sceneGraph_hpp

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <gsl/pointers>
#include "../Lights/Lights.hpp"
#include <array>
#include <string>

class Camera;
class GameObject;

class SceneGraph{
protected:
    std::array<LightData,k_lightCount> m_lights;
    std::vector<gsl::owner<GameObject*>> m_objs;  // This is a vector of pointers to the objects in the scene, this allows us to render everything in the scene by adding to this vector of objects no matter if its a modelObject single or instanced.
    gsl::owner<Camera*> p_camera;
    glm::vec3 m_playerPosition;
public:
    SceneGraph() noexcept;
    virtual ~SceneGraph() noexcept;
    virtual void Update(double deltaTime) noexcept = 0;
    
    std::vector<GameObject*> GetObjs() noexcept;
    Camera* GetCamera() noexcept;
    std::array<LightData,k_lightCount> GetLights() noexcept;
    glm::vec3 GetPlayerPosition() noexcept;

    virtual void UsePrimary() noexcept = 0;
    virtual void UseSecondary() noexcept = 0;
    virtual void Turn(GLfloat yaw, GLfloat pitch) noexcept = 0;

    void Deserialise(std::string file);
};


#endif /* sceneGraph_hpp */
