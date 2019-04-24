#version 410 core

// This is our most basic fragment shader

out vec4 color; // We will be outputing the vec4 for colour of each fragment

in VS_OUT // we accept in the VS_OUT
{
    vec2 tc; // which contains a vec2 called tc, ie our texture coordinates
} fs_in; // and we will assign it to the variable fs_in, so it can be accessed in the format fs_in.tc

uniform sampler2D tex; // We need to grab the texture from the uniform

void main(void)
{
    color = vec4( texture(tex, fs_in.tc).xyz, 1.0); // So all we need to do is use the texture function to assign the colours appropriately using the texture coordinates.
}

