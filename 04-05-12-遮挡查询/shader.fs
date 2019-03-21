#version 330 core

in vec4 color;

out vec4 fColor;


void main()
{    

	if(color.a < 0.2f){
		discard;
	}
	fColor = color;

}