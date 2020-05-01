#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitTangents;

out VS_OUT
{
    vec2 tc;
    vec4 fragPos;
    mat3 TBN;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 mv;
uniform mat4 mvp;

void main(void)
{

    // How learnOpenGl
//    vec3 T = (vec3(modelMatrix * vec4(tangents, 0.0)));
//    vec3 N = (vec3(modelMatrix * vec4(normals, 0.0)));
//    vec3 B = (vec3(modelMatrix * vec4(bitTangents, 0.0)));
//    vs_out.TBN = inverse(mat3(T, B, N));

    mat3 TBN = mat3(tangents, bitTangents, normals);
//    vs_out.TBN = TBN;
    vs_out.TBN = inverse(mat3(modelMatrix) * TBN);

    vs_out.tc = tc;
    vs_out.fragPos = modelMatrix * position;

    gl_Position = mvp * position;
}
