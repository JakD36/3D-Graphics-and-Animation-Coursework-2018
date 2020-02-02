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

uniform mat4 mvp;
void main(void)
{
    gl_Position = mvp * position; // apply all our coordinate transformations,
    vs_out.tc = tc; // make sure to assign our texture coordinates to the output of the shader
}