#version 330 core

layout (std140) uniform Uniforms{
	vec3 translation;
	float scale;
	bool enabled;
	vec4 rotation;
};

in vec4 fColor;
out vec4 color;

void main(){
	color = fColor;
}