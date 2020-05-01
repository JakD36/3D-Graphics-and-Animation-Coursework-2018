#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec4 normals;

out VS_OUT
{
    vec2 tc;
    vec3 normals;
    vec3 fragPos;
} vs_out;


uniform mat4 modelMatrix;
uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * position;

    vs_out.tc = tc;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix))); // Convert normals to world space
    vs_out.normals = normalMatrix * normals.xyz;

    vs_out.fragPos = (modelMatrix * position).xyz;
}
