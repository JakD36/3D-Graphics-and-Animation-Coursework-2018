#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec4 normals;

uniform mat4 mvp;
uniform float thickness;

void main(void)
{
    gl_Position = mvp * (position + thickness * normals);
}
