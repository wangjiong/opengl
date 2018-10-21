#version 330 core

in vec3 color;

out vec4 FragColor;

void main()
{    
	FragColor = vec4(color,0);

	//FragColor = vec4(1,0,1,0);
}