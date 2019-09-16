#ifndef Render_hpp
#define Render_hpp

#include <stdio.h>
#include <vector>

#include "../Scenes/SceneGraph.hpp"
#include "Camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "../Shaders/ShaderPipeline.hpp"

#include <queue>
#include <list>

#include <iostream>

#include "../Utils/Profile.h"

using namespace std;

class RenderManager{
private:
    list<GameObject*> m_renderList;
    list<GameObject*>::iterator m_iterator;

    queue<GameObject*> m_addUpdateQueue;
    queue<GameObject*> m_removeQueue;

    
public:
    void Batch(); // TODO: Make Private!

    void QueueToAddOrUpdate(GameObject*);
    void QueueToRemove(GameObject*);

    void Render();
};

#endif