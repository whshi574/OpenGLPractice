#version 330 core
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;

out vec4 OutColor;
out vec2 OutUV;

uniform mat4 ViewMatrix;
uniform mat4 ProjMatrix;
uniform mat4 ModelMatrix;

void main()
{
    gl_Position = ProjMatrix * ViewMatrix * ModelMatrix * vec4(inPosition, 1.0);
    OutColor = vec4(inColor, 1.0f);
    OutUV = inUV;
};