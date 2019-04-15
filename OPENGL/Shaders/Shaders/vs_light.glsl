#version 410 core

// This is a basic vertex shader, we tell the shader where to find position, tc, and normals in the buffer
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec4 normals;

// We sort our output for the shader, we will out VS_OUT with the x,y texture coordinates tc
out VS_OUT
{
    vec2 tc;
} vs_out;

// Then tell the shader the variables to grab from the uniform
uniform mat4 modelMatrix; // The model matrix that has been concatenated to include translations,rotations and scale
uniform mat4 proj_matrix; // our matrix to apply our perspective to the scene
uniform mat4 viewMatrix;  // the view matrix to be able to see from the cameras perspective

void main(void)
{
    gl_Position = proj_matrix * viewMatrix * modelMatrix * position; // apply all our coordinate transformations,
    // model space - model transform -> world space - view transform -> view space
    // view space - proj transform -> normalised space - viewport transform -> screen space
    
    // we do the viewport transformation with glViewport function in the main render function for each framebuffer
    vs_out.tc = tc; // make sure to assign our texture coordinates to the output of the shader
}
