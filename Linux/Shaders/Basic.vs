#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;

out vec4 Color;

uniform mat4 gProjection;
uniform mat4 gView;
uniform mat4 gWorld;

void main()
{
    gl_Position = gProjection * gView * gWorld * vec4(vPosition, 1);
	Color = vColor;
}