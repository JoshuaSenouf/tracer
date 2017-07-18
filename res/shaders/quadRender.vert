#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;
out vec3 outColor;


void main()
{
    TexCoords = texCoords;
    outColor = vec3(1.0f, 0.0f, 0.0f);

    gl_Position = vec4(position, 1.0);
}
