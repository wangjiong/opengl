#version 330 core

in vec4 color;

//out vec4 fColor;


void main()
{    

	//fColor = color;
	//gl_FragColor = color;
	gl_FragData[0] = vec4(1,0,0,1);
	gl_FragData[1] = vec4(0,1,0,1);
	gl_FragData[2] = vec4(0,0,1,1);
}