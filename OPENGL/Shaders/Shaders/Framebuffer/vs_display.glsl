#version 410 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;


// Simply to assign the vertex positions, and pass the texture coordinates to the fragment shader
void main() {
    gl_Position = vec4(position.x*2-1, position.y*2-1, 0.0f, 1.0f); // Turns out I was not rendering to in clip space, I was rendering in 0 - 1 not -1 to 1, which caused the weird issue with the viewport being in the top right.
    TexCoords = texCoords;
}
