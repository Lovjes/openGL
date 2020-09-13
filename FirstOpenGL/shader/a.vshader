#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 atexCoord;

out vec2 texCoord;
out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos, 1.f);
	ourColor = aColor;
	texCoord = atexCoord;
}