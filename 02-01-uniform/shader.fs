#version 330 core

in vec4 color;

out vec4 fColor;


void main()
{    
	//fColor = vec4(0,1,1,1);
	fColor = color;
}