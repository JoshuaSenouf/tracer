#version 330 core

in vec2 TexCoords;

out vec4 outputColor;


uniform sampler2D renderResult;



void main()
{
    vec3 color = texture(renderResult, TexCoords).rgb;

    outputColor = vec4(color, 1.0f);
}
