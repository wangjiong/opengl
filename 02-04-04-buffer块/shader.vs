#version 330 core

layout (location = 0) in vec4 vPos;

/* Ϊʲô�ᱨ����
buffer BufferObject {
	int mode;
	vec4 points[];
};
*/

void main(){
	gl_Position = vPos;
}