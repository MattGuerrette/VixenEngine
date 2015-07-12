#version 430 core

in vec3 Position;
out vec3 vPosition;

void main()
{
    vPosition = Position;
}