#version 330 core
layout (location = 0) in vec4 vPosition;

out vec4 color;

uniform vec4 incolor;

void main()
{
	color = incolor;
	//color = vec4(0,1,0,1);
    gl_Position = vPosition;
}