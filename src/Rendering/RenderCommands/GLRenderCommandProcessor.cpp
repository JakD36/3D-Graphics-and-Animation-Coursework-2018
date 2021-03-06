//
// Created by Jack on 02/03/2021.
//

#include "GLRenderCommandProcessor.h"
#include "RenderCommands.h"

#include <memory>
#include <vector>
#include <imgui.h>
#include "../RenderTarget.h"
#include "../Shaders/ShaderManager.h"
#include "../../GameObject/GameObject.hpp"
#include "../../Scenes/SceneGraph.hpp"
#include "../Views/Camera.hpp"
#include "../../Core/Application/Window.h"
#include <thread>

using namespace std;

void GLRenderCommandProcessor::Process(Window *window, vector<unique_ptr<RenderCommand>> renderQueue)
{
    ShaderManager* shaderManager = ShaderManager::GetInstance();
    auto framebufferProg = shaderManager->RequestProgram("Shaders/vs_display.glsl","Shaders/fs_display.glsl");
    auto testProg = shaderManager->RequestProgram("Shaders/dvert.glsl","Shaders/dfrag.glsl");

    auto* glWindow = (GLFWwindow*)window->GetNativeWindow();

    glfwMakeContextCurrent(nullptr);

    thread render([=](GLFWwindow* window, vector<unique_ptr<RenderCommand>> renderQueue){
        glfwMakeContextCurrent(glWindow);
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

                case RenderCommand::Type::CLEAR:
                    ASSERT(false,"Render Command not implemented.");
                    // Clear all commands in command buffer, // todo: unsure on how that fits with this approach
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

                case RenderCommand::Type::CLEAR_RENDER_TARGET:
                {
                    auto clearCmd = static_cast<const ClearRenderTargetCmd*>(cmd.get());
                    if(clearCmd->m_clearDepth)
                        glClearDepth(clearCmd->m_depth);

                    if(clearCmd->m_clearColour)
                        glClearBufferfv(GL_COLOR, 0, &clearCmd->m_colour[0]);
                }
                    break;

                case RenderCommand::Type::COPY_TEXTURE:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::DRAW_MESH: // todo implement actual pass in mesh shit
                {
                    ASSERT(false,"Render Command not implemented.");
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

                case RenderCommand::Type::DRAW_MESH_INSTANCED:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::DRAW_MESH_INSTANCED_INDIRECT:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::DRAW_RENDERER:
                        ASSERT(false,"Render Command not implemented.");
                        break;

                case RenderCommand::Type::ENABLE_SCISSOR_RECT:
                {
                    auto scissorCmd = static_cast<const EnableScissorRectCmd*>(cmd.get());
                    auto& rect = scissorCmd->m_rect;
                    glEnable(GL_SCISSOR_TEST);
                    glScissor(rect.x,rect.y,rect.z,rect.w);
                }
                    break;

                case RenderCommand::Type::DISABLE_SCISSOR_RECT:
                    glDisable(GL_SCISSOR_TEST);
                    break;

                case RenderCommand::Type::GENERATE_RT_MIPS:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::GET_TMP_RT:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::GET_TMP_RT_ARRAY:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_BUFFER:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_FLOAT:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_FLOAT_ARRAY:
                    ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_INT:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_MATRIX:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_MATRIX_ARRAY:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_TEXTURE:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_VECTOR:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_GLOBAL_VECTOR_ARRAY:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_PROJECTION_MATRIX:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_VIEW_MATRIX:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_VIEW_PROJECTION_MATRICES:
                ASSERT(false,"Render Command not implemented.");
                    break;

                case RenderCommand::Type::SET_RENDER_TARGET:
                {
                    auto setRt = static_cast<const SetRenderTargetRenderCommand*>(cmd.get());
                    tmpRT = setRt->m_rt;
                    tmpRT.Bind();
                }
                    break;

                case RenderCommand::Type::SET_VIEWPORT:
                ASSERT(false,"Render Command not implemented.");
                    break;




                case RenderCommand::Type::DRAW_RENDERERS:
                {
                    auto drawCmd = static_cast<const DrawRenderers*>(cmd.get());
                    vector<GameObject>& objs = drawCmd->m_scene->GetObjs();
                    // frustum culling

                    std::for_each(begin(objs),end(objs),[&](GameObject &obj) // TODO: Verify why when this copies it causes the entire mesh line up to be deleted
                    {
                        obj.Render(*drawCmd->m_camera);
                    });
                }
                    break;

            }
        }

        renderQueue.clear();
        glfwMakeContextCurrent(nullptr);

    },glWindow,std::move(renderQueue));

    render.join();
    glfwMakeContextCurrent(glWindow);
}