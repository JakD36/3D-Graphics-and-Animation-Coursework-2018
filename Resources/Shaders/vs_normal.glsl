#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec3 normals;
layout (location = 3) in vec3 tangents;
layout (location = 4) in vec3 bitangents;

out VS_OUT
{
    vec2 tc;
    vec4 fragPos;
    mat3 TBN;
    vec3 normals;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 mv;
uniform mat4 mvp;

void main(void)
{

    // How learnOpenGl
    
   vec3 T = normalize(modelMatrix * vec4(tangents, 0.0)).xyz; // w = 0, to avoid any translation
   vec3 N = normalize((modelMatrix * vec4(normals, 0.0)).xyz);
   vec3 B = normalize(modelMatrix * vec4(bitangents, 0.0)).xyz;

   mat3 worldToTangent = mat3(T.x, B.x, N.x, T.y, B.y, N.y, T.z, B.z, N.z); // our world to tangent TBN matrix 
   mat3 tangentToWorld = transpose(worldToTangent);

   vs_out.TBN = mat3(T,B,N); // A tangent to world ...

    vs_out.tc = tc;
    vs_out.fragPos = modelMatrix * position;
    vs_out.normals = normals;

    gl_Position = mvp * position;
}
