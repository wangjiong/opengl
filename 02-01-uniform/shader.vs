#version 330 core
layout (location = 0) in vec4 vPosition;

out vec4 color;

uniform mat4 ModelViewProjectionMatrix;

void main()
{
	color = ModelViewProjectionMatrix[3];
    gl_Position = vPosition;
}