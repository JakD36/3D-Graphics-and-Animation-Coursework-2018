#version 410 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec4 normals;

out VS_OUT
{
    vec2 tc;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 proj_matrix;
uniform mat4 viewMatrix;

void main(void)
{
    gl_Position = proj_matrix * viewMatrix * modelMatrix * position;
    vs_out.tc = tc;
}