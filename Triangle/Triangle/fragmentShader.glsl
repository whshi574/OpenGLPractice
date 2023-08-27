#version 330 core
out vec4 fragColor;

in vec4 OutColor;
in vec2 OutUV;

uniform vec4 FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform sampler2D OurTexture;

void main()
{
    fragColor = texture(OurTexture, OutUV);
};