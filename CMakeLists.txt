cmake_minimum_required(VERSION 3.15)
project(3D_Graphics_and_Animation_Coursework_2018)

set(CMAKE_CXX_STANDARD 17)

include_directories(Include)

add_executable(3D_Graphics_and_Animation_Coursework_2018
        Include/DearImgui/imgui.cpp
        Include/DearImgui/imgui_demo.cpp
        Include/DearImgui/imgui_draw.cpp
        Include/DearImgui/imgui_impl_glfw.cpp
        Include/DearImgui/imgui_impl_opengl3.cpp
        Include/DearImgui/imgui_widgets.cpp

        Include/glm/detail/glm.cpp

        Resources/Shaders/fs.glsl
        Resources/Shaders/fs_display.glsl
        Resources/Shaders/fs_light.glsl
        Resources/Shaders/vs.glsl
        Resources/Shaders/vs_display.glsl
        Resources/Shaders/vs_light.glsl

        src/Controllers/controller.cpp
        src/Controllers/controller.hpp
        src/Controllers/keyboardAndMouse.cpp
        src/Controllers/keyboardAndMouse.hpp

        src/GameObject/GameObject.cpp
        src/GameObject/GameObject.hpp

        src/Lights/Lights.hpp

        src/Material/Material.cpp
        src/Material/Material.hpp

        src/Mesh/MeshResource.cpp
        src/Mesh/MeshResource.hpp

        src/Scenes/Scene1.cpp
        src/Scenes/Scene1.hpp
        src/Scenes/SceneGraph.cpp
        src/Scenes/SceneGraph.hpp

        src/Texture/Texture.cpp
        src/Texture/Texture.hpp

        src/Profiling/ProfilerService.cpp
        src/Profiling/ProfilerService.h
        src/Utils/VectorUtils.hpp

        src/Views/camera.cpp
        src/Views/camera.hpp
        src/Views/Renderer.cpp
        src/Views/Renderer.hpp

        src/main.cpp
        src/Shaders/ShaderManager.cpp
        src/Shaders/ShaderManager.h
        src/Shaders/ShaderUtils.h
        src/Shaders/ShaderUtils.cpp
        src/Utils/VectorUtils.cpp
        src/Framebuffer/TwoPassFramebuffer.cpp
        src/Framebuffer/TwoPassFramebuffer.h
        src/Lights/Lights.cpp
        src/OpenGLCallbacks.h
        src/OpenGLCallbacks.cpp src/OpenGLSetup.cpp src/OpenGLSetup.h src/FSM/FSM.cpp src/FSM/FSM.h src/FSM/Flowstate.cpp src/FSM/Flowstate.h src/Profiling/ProfileTag.cpp src/Profiling/ProfileTag.h src/Transform.cpp src/Transform.h src/Utils/DebugUtils.h src/RenderPass.h src/Utils/imgui_impl_glm.h src/Utils/ShaderEditor.cpp src/Utils/ShaderEditor.h src/Views/RenderTask.cpp src/Views/RenderTask.h src/RenderPass.cpp src/ResourceManager/SparseVector.h src/ResourceManager/ResourceManager.h src/Mesh/Mesh.cpp src/Mesh/Mesh.h src/Resource.h src/Material/MaterialResource.cpp src/Material/MaterialResource.h src/Texture/TextureResource.cpp src/Texture/TextureResource.h src/Resource.cpp src/Views/RenderTaskResource.cpp src/Views/RenderTaskResource.h src/Framebuffer/FramebufferBase.cpp src/Framebuffer/FramebufferBase.h src/Framebuffer/SinglePassFramebuffer.cpp src/Framebuffer/SinglePassFramebuffer.h src/Framebuffer/ImGuiFramebuffer.cpp src/Framebuffer/ImGuiFramebuffer.h src/Profiling/MemoryProfiler.cpp src/Profiling/MemoryProfiler.h src/Profiling/ProfilerWindow.cpp src/Profiling/ProfilerWindow.h)

if(APPLE)
    find_library( COCOA_FW Cocoa )
    find_library( OPENGL_FW OpenGL )
    find_library( IOKIT_FW IOKit )
    find_library( COREFOUNDATION_FW CoreFoundation )
    find_library( COREVIDEO_FW CoreVideo )
    find_library( GLEW GLEW Frameworks)
    find_library( GLFW glfw3 Frameworks)
    find_library( ASSIMP assimp Frameworks)

    target_link_libraries(3D_Graphics_and_Animation_Coursework_2018
            ${GLFW}
            ${GLEW}
            ${ASSIMP}
            ${COCOA_FW}
            ${OPENGL_FW}
            ${IOKIT_FW}
            ${COREFOUNDATION_FW}
            ${COREVIDEO_FW})
endif()

if(WIN32)
    find_library( GLEW_S glew32s Frameworks)
    find_library( GLFW glfw3 Frameworks)
    find_package(OpenGL REQUIRED)

    target_link_libraries(3D_Graphics_and_Animation_Coursework_2018
            ${GLFW}
            ${GLEW_S}
            ${OPENGL_LIBRARIES}
            )
endif()