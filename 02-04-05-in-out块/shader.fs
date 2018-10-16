#version 330 core

out vec4 color;

in Lighting {
	vec3 normal;
	vec2 bumpCoord;
};

void main(){
	color = vec4(1 , bumpCoord,0);
}