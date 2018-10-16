#version 330 core

layout (location = 0) in vec4 vPos;

out Lighting {
	vec3 normal;
	vec2 bumpCoord;
};

void main(){
	normal = vec3(1,0,0);
	bumpCoord = vec2(0,1);

	gl_Position = vPos;
}