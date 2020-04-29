#version 410 core

//The more complex vertex shader that is used for the majority of the objects in the scene

// Grab the variables from the buffer
layout (location = 0) in vec4 position; // Position of the object
layout (location = 1) in vec2 tc;       // Texture coordinates (ie uv coords)
layout (location = 2) in vec4 normals;  // Normals for each triangle

// Set our outputs to the fragment shader
out VS_OUT
{
    vec2 tc;        // output the uv coordinates as texture coordinates tc
    vec4 normals;   // pass on the normals for use in lighting calculation
    vec4 fragPos;   // pass on the coordinates in the world space of the fragment
} vs_out;

// Grab our different matrices from the uniforms for use in calculations below
uniform mat4 modelMatrix;
uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * position;// apply all our coordinate transformations,
    // model space - model transform -> world space
    // world space - view transform -> view space
    // view space - proj transform -> normalised space
    // normalised space - viewport transform -> screen space

    vs_out.tc = tc; // assign our texture coordinats to the output

    // get normals for the light calculations in the fragment shader
    // and the fragments position for the light calculation
    vec3 normalsT = mat3(transpose(inverse(modelMatrix))) * vec3(normals.xyz);
    vs_out.normals = vec4(normalsT,1.0);
    vs_out.fragPos = modelMatrix * position ; // This gives the fragments position in the world space, as we are performing a model transformation.
}
