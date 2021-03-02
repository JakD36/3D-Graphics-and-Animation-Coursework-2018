cmake_minimum_required(VERSION 3.15)
project(3D_Graphics_and_Animation_Coursework_2018)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory (extern EXCLUDE_FROM_ALL)

set(extern_libs
        assimp
        libglew_static
        glfw
        glm
        gli
        GSL
        )

include_directories(
        Include
        extern/imgui
)

add_executable(3D_Graphics_and_Animation_Coursework_2018
        src/Core/Imgui.cpp

        Resources/Shaders/fs.glsl
        Resources/Shaders/fs_display.glsl
        Resources/Shaders/fs_light.glsl
        Resources/Shaders/vs.glsl
        Resources/Shaders/vs_display.glsl
        Resources/Shaders/vs_light.glsl

        src/GameObject/GameObject.cpp
        src/GameObject/GameObject.hpp

        src/Rendering/Lights/Lights.hpp

        src/Rendering/Material/Material.cpp
        src/Rendering/Material/Material.hpp

        src/Rendering/Mesh/MeshResource.cpp
        src/Rendering/Mesh/MeshResource.hpp

        src/Scenes/Scene1.cpp
        src/Scenes/Scene1.hpp
        src/Scenes/SceneGraph.cpp
        src/Scenes/SceneGraph.hpp

        src/Rendering/Texture/Texture.cpp
        src/Rendering/Texture/Texture.hpp

        src/Profiling/ProfilerService.cpp
        src/Profiling/ProfilerService.h
        src/Utils/MathUtils.hpp

        src/Rendering/Views/camera.cpp
        src/Rendering/Views/camera.hpp
        src/Rendering/Renderer.cpp
        src/Rendering/Renderer.hpp

        src/main.cpp
        src/Rendering/Shaders/ShaderManager.cpp
        src/Rendering/Shaders/ShaderManager.h
        src/Rendering/Shaders/ShaderUtils.h
        src/Rendering/Shaders/ShaderUtils.cpp
        src/Utils/MathUtils.cpp
        src/Rendering/Lights/Lights.cpp
        src/FSM/FSM.cpp
        src/FSM/FSM.h
        src/FSM/Flowstate.cpp
        src/FSM/Flowstate.h
        src/Profiling/ProfileTag.cpp
        src/Profiling/ProfileTag.h
        src/GameObject/Transform.cpp
        src/GameObject/Transform.h
        src/Utils/DebugUtils.h
        src/Rendering/Views/RenderPass.h
        src/Rendering/ImGui/imgui_impl_glm.h
        src/Rendering/ImGui/ShaderEditorWindow.cpp
        src/Rendering/ImGui/ShaderEditorWindow.h
        src/Rendering/Views/RenderTask.cpp
        src/Rendering/Views/RenderTask.h
        src/Rendering/Views/RenderPass.cpp
        src/Utils/Collections/SparseVector.h
        src/ResourceManager/ResourceManager.h
        src/Rendering/Mesh/Mesh.cpp
        src/Rendering/Mesh/Mesh.h
        src/ResourceManager/Resource.h
        src/Rendering/Material/MaterialResource.cpp
        src/Rendering/Material/MaterialResource.h
        src/Rendering/Texture/TextureResource.cpp
        src/Rendering/Texture/TextureResource.h
        src/ResourceManager/Resource.cpp
        src/Rendering/Views/RenderTaskResource.cpp
        src/Rendering/Views/RenderTaskResource.h
        src/Profiling/MemoryProfiler.cpp
        src/Profiling/MemoryProfiler.h
        src/Profiling/ProfilerWindow.cpp
        src/Profiling/ProfilerWindow.h
        src/Core/OpenGL/GlWindow.cpp
        src/Core/OpenGL/GlWindow.h
        src/Core/Application/Application.h
        src/Core/Application/Window.h
        src/Workshop.cpp src/Workshop.h
        src/Core/WindowEvent.h
        src/Core/Input/Input.h
        src/Core/Input/KeyCodes.h
        src/Core/Input/MouseCodes.h
        src/Core/Input/Input.cpp
        src/Core/EnumBitmask.h src/Rendering/RenderCommands/RenderCommand.cpp src/Rendering/RenderCommands/RenderCommand.h src/Rendering/RenderCommands/Commands/BeginRenderCommand.cpp src/Rendering/RenderCommands/Commands/BeginRenderCommand.h src/Rendering/RenderCommands/Commands/EndRenderCommand.cpp src/Rendering/RenderCommands/Commands/EndRenderCommand.h src/Rendering/RenderCommands/Commands/BlitRenderCommand.cpp src/Rendering/RenderCommands/Commands/BlitRenderCommand.h src/Rendering/RenderCommands/Commands/SetRenderTargetRenderCommand.cpp src/Rendering/RenderCommands/Commands/SetRenderTargetRenderCommand.h src/Rendering/RenderCommands/Commands/BeginWithRtRenderCommand.cpp src/Rendering/RenderCommands/Commands/BeginWithRtRenderCommand.h src/Rendering/RenderCommands/RenderCommands.h src/Rendering/RenderCommands/Commands/DrawMeshCommand.h src/Rendering/RenderCommands/Commands/DrawRenderers.h src/Rendering/RenderTarget.cpp src/Rendering/RenderTarget.h src/Core/Imgui.cpp)

if(APPLE)
    SET (CMAKE_CXX_FLAGS "-fsized-deallocation")

    find_library( COCOA_FW Cocoa )
    find_library( OPENGL_FW OpenGL )
    find_library( IOKIT_FW IOKit )
    find_library( COREFOUNDATION_FW CoreFoundation )
    find_library( COREVIDEO_FW CoreVideo )

    target_link_libraries(3D_Graphics_and_Animation_Coursework_2018
            ${COCOA_FW}
            ${OPENGL_FW}
            ${IOKIT_FW}
            ${COREFOUNDATION_FW}
            ${COREVIDEO_FW}

            ${extern_libs}
            )

elseif(WIN32)

    find_package( OpenGL REQUIRED )

    target_link_libraries(3D_Graphics_and_Animation_Coursework_2018
            ${OPENGL_LIBRARIES}
            ${extern_libs}
            )
endif()

target_precompile_headers(3D_Graphics_and_Animation_Coursework_2018
#        PUBLIC
#        project_header.h
        PRIVATE
        <functional>
        <iostream>
        <thread>
        <algorithm>
        <string>
        <array>
        <set>
        <deque>
        <map>
        <unordered_set>
        <unordered_map>
        <vector>
        <memory>
        [["glm/glm.hpp"]]
        [["gli/gli.hpp"]]
        [["json.hpp"]]
        [["imgui.h"]]
        [["GL/glew.h"]]
        [["GLFW/glfw3.h"]]
        )
