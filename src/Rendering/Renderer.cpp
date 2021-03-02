#include "Renderer.hpp"

#include <memory>
#include <vector>
#include <imgui.h>
#include "Views/Camera.hpp"
#include "../Profiling/ProfilerService.h"
#include "Shaders/ShaderManager.h"
#include "Lights/Lights.hpp"
#include "../GameObject/GameObject.hpp"
#include "../Scenes/SceneGraph.hpp"

#include "RenderCommands/RenderCommands.h"
#include "RenderTarget.h"
#include "RenderCommands/GLRenderCommandProcessor.h"

#include "../Core/Application/Window.h"


using namespace std;

Renderer::Renderer(Window* window) noexcept {
    PROFILE(profiler,"Renderer Initialisation");


    glfwGetWindowSize((GLFWwindow*)window->GetNativeWindow(), &m_windowWidth, &m_windowHeight);

    m_cmdProc = std::make_unique<GLRenderCommandProcessor>();

    // On high DPI, there are a higher number of pixels in the window than the length of the window, so we need to use the frameWidth and height,
    int frameWidth, frameHeight;
    glfwGetFramebufferSize((GLFWwindow*)window, &frameWidth, &frameHeight);

    // TwoPassFramebuffer operations
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);    // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_CULL_FACE); // These lines prevent faces facing away from the camera from being rendered
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    ENDPROFILE(profiler);
}

Renderer::~Renderer() noexcept
{
}

void Renderer::Render(Window* window, SceneGraph* scene) noexcept{
    PROFILE(profiler,"Render");

    int frameWidth, frameHeight;
    glfwGetFramebufferSize((GLFWwindow*)window->GetNativeWindow(), &frameWidth, &frameHeight);

    // Set Environment variables
    Camera* camera = scene->GetCamera();
    glm::vec3 camPos = camera->GetPosition();
    glm::mat4 viewMatrix = camera->BuildViewMat();
    glm::mat4 projMatrix = camera->ProjectionMatrix();
    array<LightData,k_lightCount> lights = scene->GetLights();

    vector<ProgramInfo> programs = ShaderManager::GetInstance()->GetShaderPrograms();
    for(int i = 0, n = programs.size(); i < n; ++i)
    {
        // Link lighting
        GLuint index = glGetUniformBlockIndex(programs[i].program,"lightBlock");
        if(index != GL_INVALID_INDEX)
            glUniformBlockBinding(programs[i].program, index, 0);

        // Link Time

        // Link camera position
    }
    // Update lights
    lights[2].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[2].spotOuterCutOff = glm::cos(glm::radians(20.0f));

    lights[3].spotCutOff = glm::cos(glm::radians(15.0f));
    lights[3].spotOuterCutOff = glm::cos(glm::radians(20.0f));
    m_lightUbo.UpdateData(lights.data());

    // TEST CODE
    RenderTarget rt(RenderTarget::Type::CUSTOM, {frameWidth,frameHeight});
    RenderTarget bkBuffer(RenderTarget::Type::BACK_BUFFER, {frameWidth,frameHeight});

    vector<unique_ptr<RenderCommand>> renderQueue;
//    renderQueue.push_back(std::move(std::unique_ptr<BeginRenderCommand>(new BeginRenderCommand({0,0},{frameWidth,frameHeight},{1,1,0,1}))));
//    renderQueue.push_back(std::move(std::unique_ptr<SetRenderTargetRenderCommand>(new SetRenderTargetRenderCommand(rt,1))));
    renderQueue.push_back(std::move(std::make_unique<BeginWithRtRenderCommand>(rt)));
//    renderQueue.push_back(std::move(std::unique_ptr<DrawMeshCommand>(new DrawMeshCommand())));
    renderQueue.push_back(std::move(std::make_unique<DrawRenderers>(scene, camera)));
//    renderQueue.push_back(std::move(std::unique_ptr<BlitRenderCommand>(new BlitRenderCommand(rt,bkBuffer,1))));
    renderQueue.push_back(std::move(std::make_unique<EndRenderCommand>()));

    // Execute Commands on a different thread!
    m_cmdProc->Process(window,std::move(renderQueue));

    // Set the framebuffer to the imgui window
    ImGui::Begin("Viewport",NULL);
    ImGui::Image((void*)rt.m_colourAttachment, ImVec2(rt.m_resolution.x * 0.25f, rt.m_resolution.y * 0.25f), ImVec2(0,1), ImVec2(1,0), ImVec4(1.0f,1.0f,1.0f,1.0f), ImVec4(1.0f,1.0f,1.0f,0.5f));
    ImGui::End();

    glBindFramebuffer(GL_FRAMEBUFFER,0);

    ENDPROFILE(profiler);
}