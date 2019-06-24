#version 330 core
layout (location = 0) in vec2 aPos;

out vec2 outValue;

void main()
{
	outValue.x = aPos.x + 0.001;
	outValue.y = aPos.y;

    gl_Position = vec4(aPos, 1.0, 1.0);
}