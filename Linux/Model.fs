#version 430 core

in vec2 TexCoord;
in vec3 NormalCoord;
uniform sampler2D gDiffuse;
uniform sampler2D gBump;

void main()
{
    vec2 texCoord = vec2(TexCoord.s, 1.0f - TexCoord.t);
    gl_FragColor = texture2D(gDiffuse, texCoord.st);
}