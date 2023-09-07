#version 330 core
out vec4 fragColor;

in vec4 OutColor;
in vec2 OutUV;

uniform vec4 LightColor;
uniform float AmbientStrength = 0.5f;
uniform sampler2D OurTexture;

void main()
{
    vec4 Result = LightColor * AmbientStrength;
    fragColor = texture(OurTexture, OutUV) * Result;
};