#version 410 core

// This is the fragment shader for our framebuffer and its second pass

in vec2 TexCoords; // We accept the texture coordinates from the vertex shader
out vec4 color; // and output the final colour for each fragment

uniform sampler2D screenTexture;

#define M_PI 3.1415926535897932384626433832795

void main()
{
    color = texture(screenTexture,TexCoords); // this assigns the appropriate colour from the texture based on the coordinates
    // Here we can make any adjustments to the final colour on the screen and apply any screen effects we wish
   
  //   float cutoff = 0.5 + (sin(20 * 2 * M_PI * TexCoords.y)) / 100;
  //  	if(TexCoords.x > cutoff)
  //  	{
  //  		color = 0.5 + 1.5 * (color - 0.75);
 	// 	float average = (color.r + color.g + color.b) /3.0;
		// color = vec4(average, average, average, 1.0);
   	// }
}
