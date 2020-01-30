cmake_minimum_required(VERSION 3.15)
project(3D_Graphics_and_Animation_Coursework_2018)

set(CMAKE_CXX_STANDARD 14)

include_directories(Include)

add_executable(3D_Graphics_and_Animation_Coursework_2018
        Include/DearImgui/imgui.cpp
        Include/DearImgui/imgui_demo.cpp
        Include/DearImgui/imgui_draw.cpp
        Include/DearImgui/imgui_impl_glfw.cpp
        Include/DearImgui/imgui_impl_opengl3.cpp
        Include/DearImgui/imgui_widgets.cpp

        Include/glm/detail/glm.cpp
#
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

        src/Mesh/Mesh.cpp
        src/Mesh/Mesh.hpp

        src/ResourceManager/ResourceService.hpp

        src/Scenes/scene1.cpp
        src/Scenes/scene1.hpp
        src/Scenes/sceneGraph.cpp
        src/Scenes/sceneGraph.hpp

        src/Shaders/FragShader.cpp
        src/Shaders/FragShader.hpp
        src/Shaders/shaderLoader.cpp
        src/Shaders/shaderLoader.hpp
        src/Shaders/ShaderPipeline.cpp
        src/Shaders/ShaderPipeline.hpp
        src/Shaders/VertexShader.cpp
        src/Shaders/VertexShader.hpp

        src/Texture/Texture.cpp
        src/Texture/Texture.hpp

        src/Utils/ProfilerService.cpp
        src/Utils/ProfileService.h
        src/Utils/VectorUtils.hpp

        src/Views/camera.cpp
        src/Views/camera.hpp
        src/Views/Renderer.cpp
        src/Views/Renderer.hpp

        src/main.cpp)


find_library( COCOA_FW Cocoa )
find_library( OPENGL_FW OpenGL )
find_library( IOKIT_FW IOKit )
find_library( COREFOUNDATION_FW CoreFoundation )
find_library( COREVIDEO_FW CoreVideo )
find_library( GLEW GLEW Frameworks)
find_library( GLFW glfw3 Frameworks)

target_link_libraries(3D_Graphics_and_Animation_Coursework_2018
        ${GLFW}
        ${GLEW}
        ${COCOA_FW}
        ${OPENGL_FW}
        ${IOKIT_FW}
        ${COREFOUNDATION_FW}
        ${COREVIDEO_FW})
