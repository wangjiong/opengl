#version 330 core

layout (location = 0) in vec2 vPos;

layout (std140) uniform Uniforms{
	vec3 translation;
	float scale;
	bool enabled;
	vec4 rotation;
};

out vec4 fColor;

void main(){
	vec3 pos = vec3(vPos , 0.0);
	float angle = radians(rotation[0]);
	vec3 axis = normalize(rotation.yzw);
	mat3 I = mat3(1.0);
	mat3 S = mat3(
		0 , -axis.z , axis.y,
		axis.z , 0 , -axis.x,
		-axis.y , axis.x , 0 );
	mat3 uuT = outerProduct(axis,axis);
	mat3 rot = uuT + cos(angle)*(I -uuT) + sin(angle) * S;
	pos *= scale;
	pos *= rot;
	pos += translation;
	fColor = vec4(scale , scale , scale ,1);
	gl_Position = vec4(pos , 1);

	if(enabled){
		fColor = vec4(0,0,1,0);
	}else{
		fColor = vec4(0,1,0,0);
	}
}