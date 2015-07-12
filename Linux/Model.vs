#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;

out vec2 TexCoord;
out vec3 NormalCoord;

uniform mat4 gProjection;
uniform mat4 gView;
uniform mat4 gWorld;

void main()
{
    gl_Position = gProjection * gView * gWorld * vec4(vPosition, 1);
    TexCoord = vTexCoord;
}