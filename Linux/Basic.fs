#version 430 core

in vec4 Color;
out vec4 FragColor;

uniform vec4 gColor;

void main()
{
    FragColor = gColor * 1.0f;
}