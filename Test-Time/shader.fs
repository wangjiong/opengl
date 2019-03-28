#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	int jj=0;
	for(int i=0;i<1000000;i++){
		for(int j=0;j<100;j++){
			jj = i*j;
		}
	}
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}