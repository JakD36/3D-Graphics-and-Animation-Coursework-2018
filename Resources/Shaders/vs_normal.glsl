#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitTangents;

out VS_OUT
{
    vec2 tc;
    mat3 TBN;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 mv;
uniform mat4 mvp;
uniform vec3 viewPosition;

void main(void)
{
    vec3 T = normalize(vec3(modelMatrix * vec4(tangents, 0.0)));
    vec3 N = normalize(vec3(modelMatrix * vec4(normals, 0.0)));
    vec3 B = normalize(vec3(modelMatrix * vec4(bitTangents, 0.0)));
    vs_out.TBN = transpose(mat3(T, B, N));

    vs_out.tc = tc;
    vs_out.TangentFragPos = vs_out.TBN * (modelMatrix * position).rgb;
    vs_out.TangentViewPos = vs_out.TBN * viewPosition;

    gl_Position = mvp * position;
}
