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

#include "../Lights/Lights.hpp"

class Camera;
class GameObject;

/** Abstract class for each scene to be based on
 Each scene should Contain the objects and lights for the scene
 The player
 and methods to access the details of these for the Renderer
*/
class SceneGraph{
protected:
    LightStruct m_lights[LIGHTSN];// Creates our array of lightStructs to store details on all the lights in the scene.
    std::vector<GameObject*> m_Objs;  // This is a vector of pointers to the objects in the scene, this allows us to render everything in the scene by adding to this vector of objects no matter if its a modelObject single or instanced.
    Camera* p_camera;
    // Do we have objects that are global to the game
    glm::vec3 m_playerPosition;
public:
    SceneGraph() noexcept;
    virtual ~SceneGraph() noexcept;
    
    // Other methods
    virtual void Update(double currentTime) noexcept = 0; // Function to update the scene, every frame based on keyframing or procedural animation
    
    std::vector<GameObject*> GetObjs() noexcept; // Return the vector of pointers to all the objects in the scene
    Camera* GetCamera() noexcept;
    LightStruct* GetLights() noexcept;
    glm::vec3 GetPlayerPosition() noexcept;
    
    /* Actions Performed!
     These are the actions that can be performed in the game
     For example, jump, move forward/backward, turn, alter direction looking at, switch light on or off.
    */
    virtual void UsePrimary() noexcept = 0;
    virtual void UseSecondary() noexcept = 0;
    virtual void Turn(GLfloat yaw, GLfloat pitch) noexcept = 0;
};


#endif /* sceneGraph_hpp */
