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
#include "../Rendering/Lights/Lights.hpp"
#include <array>
#include <string>

class Camera;
class GameObject;
class Transform;

class SceneGraph{
protected:
    struct FileInfo
    {
        std::string path;
        time_t lastModified;
    };
    FileInfo m_fileInfo;

    std::vector<std::string> m_lightKeys;
    std::array<LightData,k_lightCount> m_lights;

    std::vector<std::string> m_objectKeys;
    std::vector<GameObject> m_objs;

    gsl::owner<Camera*> p_camera;
    Transform* m_playerTransform;
public:
    SceneGraph() noexcept;
    virtual ~SceneGraph() noexcept;
    virtual void Update(double deltaTime) noexcept;
    
    std::vector<GameObject>& GetObjs() noexcept;
    Camera* GetCamera() noexcept;
    std::array<LightData,k_lightCount> GetLights() noexcept;
    glm::vec3 GetPlayerPosition() noexcept;

    virtual void UsePrimary() noexcept = 0;
    virtual void UseSecondary() noexcept = 0;
    virtual void Turn(GLfloat yaw, GLfloat pitch) noexcept = 0;

    void UpdateFile() noexcept;
    virtual void UpdateHandles() noexcept = 0;
    void Deserialise(std::string file);
};


#endif /* sceneGraph_hpp */
