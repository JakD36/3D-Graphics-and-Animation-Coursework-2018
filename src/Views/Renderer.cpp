#include "Renderer.hpp"

#include <vector>
#include <DearImgui/imgui.h>
#include "Camera.hpp"
#include "../Utils/ProfilerService.h"
#include "../Shaders/ShaderManager.h"
#include "FrameBuffer.h"
#include "../Lights/Lights.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Scenes/SceneGraph.hpp"

using namespace std;

void Renderer::SetViewport(float x, float y, float width, float height) noexcept{
    m_viewportX = x;
    m_viewportY = y;
    m_viewportWidth = width;
    m_viewportHeight = height;
}

void Renderer::SetWindowDimensions(int windowWidth, int windowHeight) noexcept{
    this->m_windowWidth = windowWidth;
    this->m_windowHeight = windowHeight;
}

// Initialise the Renderer for this viewport
Renderer::Renderer(GLFWwindow* window) noexcept {
    PROFILE(profiler,"Renderer Initialisation");

    p_window = window;

    // Grab the window dimensions for the current window, saves passing too many arguments to the constructor
    glfwGetWindowSize(p_window, &m_windowWidth, &m_windowHeight);

    // On high DPI, there are a higher number of pixels in the window than the length of the window, so we need to use the frameWidth and height,
    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);

    // TwoPassFramebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_framebuffer = make_unique<TwoPassFramebuffer>(frameWidth, frameHeight);
//    m_framebuffer = make_unique<SinglePassFramebuffer>();

    ENDPROFILE(profiler);
}

Renderer::~Renderer() noexcept
{
}

void Renderer::Render(SceneGraph* scene) noexcept{
    PROFILE(profiler,"Render");

    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);

    m_framebuffer->RenderTo();
    RenderScene(scene,0, 0, frameWidth, frameHeight);
    m_framebuffer->PostRender(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);

    ENDPROFILE(profiler);
}

void Renderer::RenderScene(SceneGraph *scene, int viewportX, int viewportY, int viewportWidth, int viewportHeight) noexcept
{
    PROFILE(profiler,"Render Scene");
    // Convert all our projected coordinates to screen coordinates for the texture
    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewportX, viewportY, viewportWidth, viewportHeight);

    glClearBufferfv(GL_COLOR, 0, &k_clearColour[0]);
    static const GLfloat one = 1.0f;

    glEnable(GL_DEPTH_TEST);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    Camera* camera = scene->GetCamera();
    glm::mat4 viewMatrix = camera->BuildViewMat();

    // Render each object
    vector<GameObject>& objs = scene->GetObjs();
    array<LightData,k_lightCount> lights = scene->GetLights();
    vector<ProgramInfo> programs = ShaderManager::GetInstance()->GetShaderPrograms();

    for(int i = 0, n = programs.size(); i < n; ++i)
    {
        GLuint index = glGetUniformBlockIndex(programs[i].program,"lightBlock");
        if(index != GL_INVALID_INDEX)
            glUniformBlockBinding(programs[i].program, index, 0);
    }

    lights[2].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[2].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    lights[3].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[3].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    m_lightUbo.UpdateData(lights.data());

    glm::vec3 camPos = camera->GetPosition();
    glm::mat4 projMatrix = camera->ProjectionMatrix();


    ImGui::Begin("Shader Tool",NULL);
    if(ImGui::TreeNode("GameObjects"))
    {
        for(int i = 0; i < objs.size(); ++i)
        {
            auto &rp = objs[i].m_renderPass;
            if(ImGui::TreeNode(objs[i].m_name.c_str()))
            {
                for(int j = 0; j < rp.size();++j)
                {
                    if(ImGui::TreeNode(("Pass " + to_string(j)).c_str()))
                    {
                        auto &pass = rp[j];
                        for(int k = 0; k < pass.m_uniformf.size();++k)
                        {
                            ImGui::SliderFloat(pass.m_uniformf[k].m_key.c_str(), &pass.m_uniformf[k].m_value,0,5);
                        }
                        for(int k = 0; k < pass.m_uniform3fv.size();++k)
                        {
                            float tmp[3] = {pass.m_uniform3fv[k].m_value.x,pass.m_uniform3fv[k].m_value.y,pass.m_uniform3fv[k].m_value.z};
                            ImGui::InputFloat3(pass.m_uniform3fv[k].m_key.c_str(), tmp);
                            pass.m_uniform3fv[k].m_value = {tmp[0],tmp[1],tmp[2]};
                        }
                        for(int k = 0; k < pass.m_uniform4fv.size();++k)
                        {
                            float tmp[4] = {pass.m_uniform4fv[k].m_value.x,pass.m_uniform4fv[k].m_value.y,pass.m_uniform4fv[k].m_value.z,pass.m_uniform4fv[k].m_value.w};
                            ImGui::InputFloat4(pass.m_uniform4fv[k].m_key.c_str(), tmp);
                            pass.m_uniform4fv[k].m_value = {tmp[0],tmp[1],tmp[2],tmp[3]};
                        }
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    ImGui::End();

    std::for_each(begin(objs),end(objs),[&](auto obj)
    {
        obj.Render(*camera);
    });
    ENDPROFILE(profiler);
}