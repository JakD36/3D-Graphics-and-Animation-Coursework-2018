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

#include <thread>

using namespace std;

Renderer::Renderer(GLFWwindow* window) noexcept {
    PROFILE(profiler,"Renderer Initialisation");
    p_window = window;

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

    ENDPROFILE(profiler);
}

Renderer::~Renderer() noexcept
{
}

void Renderer::Render(GLFWwindow* window, SceneGraph* scene) noexcept{
    PROFILE(profiler,"Render");

    int frameWidth, frameHeight;
    glfwGetFramebufferSize(p_window, &frameWidth, &frameHeight);

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
    renderQueue.push_back(std::move(std::unique_ptr<BeginWithRtRenderCommand>(new BeginWithRtRenderCommand(rt))));
//    renderQueue.push_back(std::move(std::unique_ptr<DrawMeshCommand>(new DrawMeshCommand())));
    renderQueue.push_back(std::move(std::unique_ptr<DrawRenderers>(new DrawRenderers())));
//    renderQueue.push_back(std::move(std::unique_ptr<BlitRenderCommand>(new BlitRenderCommand(rt,bkBuffer,1))));
    renderQueue.push_back(std::move(std::unique_ptr<EndRenderCommand>(new EndRenderCommand())));

    ShaderManager* shaderManager = ShaderManager::GetInstance();
    auto framebufferProg = shaderManager->RequestProgram("Shaders/vs_display.glsl","Shaders/fs_display.glsl");
    auto testProg = shaderManager->RequestProgram("Shaders/dvert.glsl","Shaders/dfrag.glsl");

    // Execute Commands on a different thread!
    thread render([=](GLFWwindow *widow, vector<unique_ptr<RenderCommand>> renderQueue){
        glfwMakeContextCurrent(window);

        RenderTarget tmpRT;

        for(const auto& cmd : renderQueue)
        {
            switch (cmd->GetType())
            {
                case RenderCommand::Type::BEGIN:
                {
                    auto begin = static_cast<const BeginRenderCommand*>(cmd.get());
                    glBindFramebuffer(GL_FRAMEBUFFER,0);
                    glViewport(begin->m_position.x, begin->m_position.y, begin->m_resolution.x, begin->m_resolution.y);

                    glEnable(GL_SCISSOR_TEST);
                    glScissor(begin->m_position.x, begin->m_position.y, begin->m_resolution.x, begin->m_resolution.y);

                    glClearBufferfv(GL_COLOR, 0, &begin->m_clearColour[0]);
                    static const GLfloat one = 1.0f;

                    glEnable(GL_DEPTH_TEST);
                    glClearBufferfv(GL_DEPTH, 0, &one);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                }
                    break;
                case RenderCommand::Type::BEGIN_WITH_RT:
                {
                    auto begin = static_cast<const BeginWithRtRenderCommand*>(cmd.get());
                    begin->m_rt.Bind();
                    glViewport(0, 0, begin->m_rt.m_resolution.x,begin->m_rt.m_resolution.y);
//
                    glEnable(GL_SCISSOR_TEST);
                    glScissor(0,0, begin->m_rt.m_resolution.x, begin->m_rt.m_resolution.y);

                    const glm::vec4 red = {0.8, 0.2, 0.2, 1};
                    glClearBufferfv(GL_COLOR, 0, &red[0]);
                    static const GLfloat one = 1.0f;

                    glEnable(GL_DEPTH_TEST);
                    glClearBufferfv(GL_DEPTH, 0, &one);

                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                }
                    break;
                case RenderCommand::Type::END:
                    break;
                case RenderCommand::Type::BLIT:
                {
                    auto blit = static_cast<const BlitRenderCommand*>(cmd.get());
                    blit->m_dest.Bind();

                    glViewport(0,0,blit->m_dest.m_resolution.x,blit->m_dest.m_resolution.y);
                    glScissor(0,0,blit->m_dest.m_resolution.x,blit->m_dest.m_resolution.y);

                    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

                    glClear(GL_COLOR_BUFFER_BIT);
                    glDisable(GL_DEPTH_TEST); // not needed as we are just displaying a single quad

                    glUseProgram(framebufferProg);

                    const glm::vec2 m_displayCoords[12] = { // Interleaved coordinates for displaying to a Quad
                            glm::vec2(-1.0f, 1.0f), // v
                            glm::vec2(0.0f, 1.0f), // uv
                            glm::vec2(-1.0f,-1.0f), // v
                            glm::vec2(0.0f, 0.0f), // uv
                            glm::vec2( 1.0f,-1.0f), // v
                            glm::vec2(1.0f, 0.0f), // uv
                            glm::vec2(-1.0f, 1.0f), // v
                            glm::vec2(0.0f, 1.0f), // uv
                            glm::vec2( 1.0f,-1.0f), // v
                            glm::vec2(1.0f, 0.0f), // uv
                            glm::vec2( 1.0f, 1.0f),// v
                            glm::vec2(1.0f, 1.0f) // uv
                    };

                    GLuint displayVao;
                    GLuint displayBuffer;
                    glGenBuffers(1, &displayBuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer);
                    glBufferData(GL_ARRAY_BUFFER,
                                 12 * sizeof(glm::vec2),
                                 &m_displayCoords[0],
                                 GL_STATIC_DRAW);

                    glGenVertexArrays(1, &displayVao);
                    glBindVertexArray(displayVao);

                    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), NULL);
                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), (GLvoid *) (sizeof(glm::vec2)));
                    glEnableVertexAttribArray(1);

                    glBindVertexArray(displayVao);

                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, blit->m_src.m_colourAttachment);

                    glDrawArrays(GL_TRIANGLES, 0, 6);
                    glBindVertexArray(0);
                }
                    break;
                case RenderCommand::Type::DRAW_MESH:
                {
                    glUseProgram(testProg);

                    const glm::vec2 m_displayCoords[12] = { // Interleaved coordinates for displaying to a Quad
                            glm::vec2(-0.5f, 0.5f), // v
                            glm::vec2(0.0f, 0.5f), // uv
                            glm::vec2(-0.5f,-0.5f), // v
                            glm::vec2(0.0f, 0.0f), // uv
                            glm::vec2( 0.5f,-0.5f), // v
                            glm::vec2(.5f, 0.0f), // uv
                    };

                    GLuint displayVao;
                    GLuint displayBuffer;
                    glGenBuffers(1, &displayBuffer);
                    glBindBuffer(GL_ARRAY_BUFFER, displayBuffer);
                    glBufferData(GL_ARRAY_BUFFER,
                                 12 * sizeof(glm::vec2),
                                 &m_displayCoords[0],
                                 GL_STATIC_DRAW);

                    glGenVertexArrays(1, &displayVao);
                    glBindVertexArray(displayVao);

                    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), NULL);
                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), (GLvoid *) (sizeof(glm::vec2)));
                    glEnableVertexAttribArray(1);

                    glBindVertexArray(displayVao);

                    glDrawArrays(GL_TRIANGLES, 0, 6);
                }
                    break;
                case RenderCommand::Type::DRAW_RENDERERS:
                {
                    vector<GameObject>& objs = scene->GetObjs();
                    // frustum culling

                    std::for_each(begin(objs),end(objs),[&](GameObject &obj) // TODO: Verify why when this copies it causes the entire mesh line up to be deleted
                    {
                        obj.Render(*camera);
                    });
                }
                    break;
                case RenderCommand::Type::SET_RENDER_TARGET:
                {
                    auto setRt = static_cast<const SetRenderTargetRenderCommand*>(cmd.get());
                    tmpRT = setRt->m_rt;
                    tmpRT.Bind();
                }
                    break;
            }
        }

        renderQueue.clear();
    },window,std::move(renderQueue));
    render.join();

    // Set the framebuffer to the imgui window
    ImGui::Begin("Viewport",NULL);
    ImGui::Image((void*)rt.m_colourAttachment, ImVec2(rt.m_resolution.x * 0.25f, rt.m_resolution.y * 0.25f), ImVec2(0,1), ImVec2(1,0), ImVec4(1.0f,1.0f,1.0f,1.0f), ImVec4(1.0f,1.0f,1.0f,0.5f));
    ImGui::End();

    glBindFramebuffer(GL_FRAMEBUFFER,0);

    ENDPROFILE(profiler);
}