#version 330 core

layout (location = 0) in vec2 vPos;

layout (std140) uniform Uniforms{
	bool enabled;
};

out vec4 fColor;

void main(){
	vec3 pos = vec3(vPos , 0.0);
	gl_Position = vec4(pos , 1);

	if(enabled){
		fColor = vec4(0,0,1,0);
	}else{
		fColor = vec4(0,1,0,0);
	}
}