#version 410 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in vec4 normals;

out VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} vs_out;

uniform mat4 modelMatrix;
uniform mat4 proj_matrix;
uniform mat4 viewMatrix;

void main(void)
{
    gl_Position = proj_matrix * viewMatrix * modelMatrix * position;
    vs_out.tc = tc;

    vec3 normalsT = mat3(transpose(inverse(modelMatrix))) * vec3(normals.xyz);
    vs_out.normals = vec4(normalsT,1.0);
    vs_out.fragPos = modelMatrix*position;
}
