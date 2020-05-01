#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitangents;

struct lightStruct
{
    int on;
    int type;

    vec4 lightPosition;
    vec4 direction;

    float lightSpotCutOff;
    float lightSpotOuterCutOff;

    vec4 id;
    vec4 is;
};

#define LIGHTS 4
layout (std140) uniform lightBlock
{
    lightStruct lights[LIGHTS];
};


out VS_OUT
{
    vec2 tc;
    vec4 fragPos;
    vec3 tangentLightPos[LIGHTS];
    vec3 tangentViewPos;
    vec3 tangentFragPos;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 mv;
uniform mat4 mvp;
uniform vec3 viewPosition;

void main(void)
{
    vec3 T = normalize(modelMatrix * vec4(tangents, 0.0)).xyz; // w = 0, to avoid any translation
    vec3 N = normalize((modelMatrix * vec4(normals, 0.0)).xyz);
    vec3 B = normalize(modelMatrix * vec4(bitangents, 0.0)).xyz;

    mat3 TBN = mat3(T,B,N); // A tangent to world
    mat3 worldToTangent = transpose(TBN); // orthogonal matrix, transpose gives inverse

    vs_out.tc = tc;
    vs_out.fragPos = modelMatrix * position;

    vs_out.tangentLightPos[0] = worldToTangent * lights[0].lightPosition.xyz;
    vs_out.tangentLightPos[1] = worldToTangent * lights[1].lightPosition.xyz;
    vs_out.tangentLightPos[2] = worldToTangent * lights[2].lightPosition.xyz;
    vs_out.tangentLightPos[3] = worldToTangent * lights[3].lightPosition.xyz;

    vs_out.tangentViewPos = worldToTangent * viewPosition;
    vs_out.tangentFragPos = worldToTangent * vs_out.fragPos.xyz;

    gl_Position = mvp * position;
}
