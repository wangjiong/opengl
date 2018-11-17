#version 330 core

in vec4 color;

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 normal;

out vec4 fColor;

void main()
{    
	fColor = color;
}