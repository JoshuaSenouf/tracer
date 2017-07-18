#version 330 core

in vec2 TexCoords;
in vec3 outColor;

out vec4 outputColor;


void main()
{
    outputColor = vec4(outColor, 1.0f);
}
