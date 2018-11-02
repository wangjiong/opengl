#version 330 core
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;

out vec4 color;

void main()
{
	color = vColor;
	//color = vec4(0,1,0,1);
    gl_Position = vPosition;
}