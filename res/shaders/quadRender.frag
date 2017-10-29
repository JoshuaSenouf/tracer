#version 330 core

in vec2 TexCoords;

out vec4 outputColor;


uniform sampler2D renderResult;

vec3 colorLinear(vec3 colorVector);
vec3 colorSRGB(vec3 colorVector);


void main()
{
    vec3 color = texture(renderResult, vec2(TexCoords.x, 1.0f - TexCoords.y)).rgb;

    outputColor = vec4(colorSRGB(color), 1.0f);
}


vec3 colorLinear(vec3 colorVector)
{
  vec3 linearColor = pow(colorVector.rgb, vec3(2.2f));

  return linearColor;
}


vec3 colorSRGB(vec3 colorVector)
{
  vec3 srgbColor = pow(colorVector.rgb, vec3(1.0f / 2.2f));

  return srgbColor;
}
