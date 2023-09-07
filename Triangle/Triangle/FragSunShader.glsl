#version 330 core
out vec4 fragColor;

in vec4 OutColor;
in vec2 OutUV;

uniform vec4 LightColor;
uniform sampler2D OurTexture;

void main()
{
    fragColor = texture(OurTexture, OutUV) + LightColor;
};