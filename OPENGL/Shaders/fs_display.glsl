#version 410 core

// This is the fragment shader for our framebuffer and its second pass

in vec2 TexCoords; // We accept the texture coordinates from the vertex shader
out vec4 color; // and output the final colour for each fragment

uniform sampler2D screenTexture;

void main()
{
    color = texture(screenTexture,TexCoords); // this assigns the appropriate colour from the texture based on the coordinates
    
    // Here we can make any adjustments to the final colour on the screen and apply any screen effects we wish
    //    float average = (color.r + color.g + color.b) /3.0;
    //    color = vec4(averag e, average, average, 1.0);
}
